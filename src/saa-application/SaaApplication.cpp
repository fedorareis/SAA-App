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
#include "Plane.h"
#include "common/Maths.h"


ServerSocket *SaaApplication::cdtiSocket = nullptr;
std::vector<Plane> planes;
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
void SocketSetup(ClientSocket &adsbSock, ClientSocket &ownSock)
{
   try
   {
      adsbSock.connect("localhost", 4000);
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
 * Takes in an AdsBReport and the OwnshipReport data and returns a vector (a list)
 * containing the adsb data converted to relative position to the ownship in the form of a plane object.
 */
Plane adsbToRelative(AdsBReport adsb, OwnshipReport ownship)
{
   std::vector<Plane> planes;
   std::string tailNumber = "Tail Number Here";
   float positionX = calcDistance(adsb.latitude(), ownship.ownship_longitude(), ownship.ownship_latitude(),
                                ownship.ownship_longitude()) * (adsb.latitude() < ownship.ownship_latitude()? -1 : 1);
   float positionY = calcDistance(ownship.ownship_latitude(), adsb.longitude(), ownship.ownship_latitude(),
                                ownship.ownship_longitude()) * (adsb.longitude() < ownship.ownship_longitude()? -1 : 1);
   float positionZ = adsb.altitude() - ownship.ownship_altitude();
   float velocityX = fpsToNmph(ownship.north()) - fpsToNmph(adsb.north());
   float velocityY = fpsToNmph(ownship.east()) - fpsToNmph((adsb.east()));
   float velocityZ = fpsToNmph(ownship.down()) - fpsToNmph(adsb.down());
   Plane adsbPlane(tailNumber, positionX, positionY, positionZ, velocityX, velocityY, velocityZ);
   return adsbPlane;
}

void SaaApplication::initSocks()
{
   //Set up server sockets
   setupSockets(6000);
   std::thread t1(acceptNetworkConnection, &this->cdtiOut, getCdtiSocket());
   //std::thread t2(acceptNetworkConnection,&this->validationOut, getCdtiSocket());

   //set up client sockets
   ClientSocket ownSock;
   ClientSocket adsbSock;
   SocketSetup(adsbSock, ownSock);
   t1.join();
   //t2.join();
   //socks.pop_back();

   processSensors(ownSock, adsbSock);
}

void processOwnship(ClientSocket &ownSock, OwnshipReport &ownship, bool & finished)
{
   while(ownSock.hasData()) {
      ownSock.operator>>(ownship); //blocking call, waits for server
      std::cout << "got ownship data\n";
      Plane ownshipPlane("Ownship", 0, 0, 0, 0, 0, 0);
      cdtiOwnship = ownshipPlane.getCDTIPlane();
   }

   finished = true;
}

void processAdsb(ClientSocket &adsbSock, OwnshipReport &ownship, bool & finished)
{
   AdsBReport adsb;
   while(adsbSock.hasData()) {
      adsbSock.operator>>(adsb); //blocking call, waits for server
      mtx.lock();
      std::cout << "got an adsb Plane\n";
      planes.push_back(adsbToRelative(adsb, ownship));
      mtx.unlock();
   }

   finished = true;
}

void SaaApplication::processSensors(ClientSocket ownSock, ClientSocket adsbSock)
{
   Correlation cor;
   Decision dec;
   CDTIReport *rep = nullptr;
   OwnshipReport ownship;

   try
   {
      bool adsbFinished = false, ownshipFinished = false;
      std::thread adsbthread(processAdsb, std::ref(adsbSock), std::ref(ownship),std::ref(adsbFinished));
      std::thread ownshipthread(processOwnship, std::ref(ownSock), std::ref(ownship),std::ref(ownshipFinished));
      while (!adsbFinished && !ownshipFinished)
      {
         std::this_thread::sleep_for(std::chrono::seconds(1));
         mtx.lock();
         std::vector<Plane> planesCopy = planes;
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