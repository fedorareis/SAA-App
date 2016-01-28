//
// Created by Kyle Piddington on 11/15/15.
//

#include <iostream>
#include <vector>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include <common/protobuf/adsb.pb.h>
#include <common/protobuf/ownship.pb.h>
#include "SaaApplication.h"
#include "Correlation.h"
#include "Decision.h"
#include <mutex>
#include <chrono>
#include <common/protobuf/tcas.pb.h>
#include "SensorData.h"
#include "common/Maths.h"


ServerSocket *SaaApplication::cdtiSocket = nullptr;
std::vector<SensorData> planes;
std::mutex mtx;
CDTIPlane* cdtiOwnship;

void acceptNetworkConnection(ServerSocket *acceptingSocket, ServerSocket *bindingSocket)
{
   bindingSocket->accept(*acceptingSocket);
   std::cout << "Server has accepted cdti socket" << std::endl;
}

/**
 * Sets up the socket connections to the test server for reading in sensor data.
 */
void SocketSetup(ClientSocket &radarSock, ClientSocket &tcasSock, ClientSocket &adsbSock, ClientSocket &ownSock)
{
   try
   {
      //radarSock.connect("localhost", 5003);
      tcasSock.connect("localhost", 5002);
      adsbSock.connect("localhost", 5001);
      ownSock.connect("localhost", 5000);
   }
   catch (SocketException)
   {
      std::cout << "failed to open socket" << std::endl;
      std::exit(-1);
   }
}

ServerSocket *SaaApplication::getCdtiSocket()
{
   return cdtiSocket;
}

void SaaApplication::setupSockets(int cdtiPort)
{
   cdtiSocket = new ServerSocket(cdtiPort);
   std::cout << "cdtiSocket initialized" << std::endl;
}

void SaaApplication::shutdown()
{
   if (cdtiSocket != nullptr)
   {
      delete cdtiSocket;
   }
}

/**
 * Takes in an adsbReport and the OwnshipReport data and returns the SensorData version of
 * the adsb data converted to relative position to the ownship.
 */
SensorData adsbToRelative(AdsBReport adsb, OwnshipReport ownship)
{
   std::string tailNumber = "Tail Number Here"; //@TODO
   float positionX = calcDistance(adsb.latitude(), ownship.ownship_longitude(), ownship.ownship_latitude(),
                                  ownship.ownship_longitude()) * (adsb.latitude() < ownship.ownship_latitude()? -1 : 1);
   float positionY = calcDistance(ownship.ownship_latitude(), adsb.longitude(), ownship.ownship_latitude(),
                                  ownship.ownship_longitude()) * (adsb.longitude() < ownship.ownship_longitude()? -1 : 1);
   float positionZ = adsb.altitude() - ownship.ownship_altitude();
   float velocityX = fpsToNmph(ownship.north()) - fpsToNmph(adsb.north());
   float velocityY = fpsToNmph(ownship.east()) - fpsToNmph((adsb.east()));
   float velocityZ = fpsToNmph(ownship.down()) - fpsToNmph(adsb.down());
   SensorData adsbPlane(tailNumber, positionX, positionY, positionZ, velocityX, velocityY, velocityZ, Sensor::adsb);
   return adsbPlane;
}

/**
 * Takes in a TcasReport and the OwnshipReport data and returns the SensorData version of
 * the tcas data converted to relative position to the ownship.
 */
SensorData tcasToRelative(TcasReport tcas, OwnshipReport ownship) //@TODO
{
   std::string tailNumber = "Tail Number Here";
   float positionX;
   float positionY;
   float positionZ;
   float velocityX;
   float velocityY;
   float velocityZ;
   SensorData tcasPlane(tailNumber, positionX, positionY, positionZ, velocityX, velocityY, velocityZ, Sensor::tcas);
   return tcasPlane;
}

void SaaApplication::initSocks()
{
   //Set up server sockets
   setupSockets(6000);
   std::thread t1(acceptNetworkConnection, &this->cdtiOut, getCdtiSocket());
   //std::thread t2(acceptNetworkConnection,&this->validationOut, getCdtiSocket());

   //set up client sockets
   ClientSocket radarSock, tcasSock, adsbSock, ownSock;
   SocketSetup(radarSock, tcasSock, adsbSock, ownSock);
   t1.join();
   //t2.join();
   //socks.pop_back();

   processSensors(ownSock, adsbSock);
}

/*
 * Thread for the ownship socket data. Reads in an ownship report and updates the shared ownship data.
 */
void processOwnship(ClientSocket &ownSock, OwnshipReport &ownship, bool &finished)
{
   while(ownSock.hasData())
   {
      ownSock.operator>>(ownship); //blocking call, waits for server
      std::cout << "got ownship data\n";
      SensorData ownshipPlane("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship);
      cdtiOwnship = ownshipPlane.getCDTIPlane();
   }
   std::cout << "Ownship Thread done\n";

   finished = true;
}

/*
 * The thread for the adsb socket data. Reads in an adsb report and adds it to the shared list of planes.
 */
void processAdsb(ClientSocket &adsbSock, OwnshipReport &ownship, bool &finished)
{
   AdsBReport adsb;
   while(adsbSock.hasData())
   {
      adsbSock.operator>>(adsb); //blocking call, waits for server
      std::cout << "got an adsb Plane\n";
      mtx.lock();
      planes.push_back(adsbToRelative(adsb, ownship));
      mtx.unlock();
   }
   std::cout << "ADSBThread done\n";

   finished = true;
}

/*
 * The thread for the tcas socket data. Reads in a tcas report and adds it to the shared list of planes.
 */
void processTcas(ClientSocket &tcasSock, OwnshipReport &ownship, bool &finished)
{
   TcasReport tcas;
   while(tcasSock.hasData())
   {
      tcasSock.operator>>(tcas); //blocking call, waits for server
      std::cout << "got an tcas Plane\n";
      mtx.lock();
      planes.push_back(tcasToRelative(tcas, ownship));
      mtx.unlock();
   }
   std::cout << "ADSBThread done\n";

   finished = true;
}

/*
 * Sets up the separate threads for the individual plane sensor sockets and contains
 * the main loop for timing when to send data on to the correlation module,
 * then the decision module, and finally onto the cdti and validation server.
 */
void SaaApplication::processSensors(ClientSocket ownSock, ClientSocket adsbSock)
{
   Correlation cor;
   Decision dec;
   CDTIReport *rep = nullptr;
   OwnshipReport ownship;

   try
   {
      bool adsbFinished = false, ownshipFinished = false;
      std::thread adsbthread(processAdsb, std::ref(adsbSock), std::ref(ownship), std::ref(adsbFinished));
      std::thread ownshipthread(processOwnship, std::ref(ownSock), std::ref(ownship), std::ref(ownshipFinished));
      while (!adsbFinished && !ownshipFinished)
      {
         std::this_thread::sleep_for(std::chrono::seconds(1));
         mtx.lock();
         std::vector<SensorData> planesCopy = planes;
         planes.clear();
         mtx.unlock();
         planesCopy = cor.correlate(planesCopy);
         dec.report(&list, &planesCopy);
         rep = dec.generateReport(&list, cdtiOwnship);
         cdtiOut << (*rep);
         //validationOut << (*rep);
         std::cout << "finished one cycle" << std::endl;
      }
      adsbthread.join();
      ownshipthread.join();
   }
   catch (SocketException)
   {
      std::cout << "got a socket exception... exiting" << std::endl;
      //run = false;
      exit(-1);
   }

   delete rep;
}