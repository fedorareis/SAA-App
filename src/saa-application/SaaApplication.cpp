/*
 * Created by Kyle Piddington on 11/15/15.
 * Main Author: Jacob Hardi
 */

#include <iostream>
#include <vector>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include <common/protobuf/adsb.pb.h>
#include "SaaApplication.h"
#include "Correlation.h"
#include "Decision.h"
#include "ServerConnectionManager.h"
#include <mutex>
#include <common/protobuf/tcas.pb.h>
#include <common/protobuf/radar.pb.h>


std::shared_ptr<ServerConnectionManager> SaaApplication::connectionManager = nullptr;
std::shared_ptr<ServerSocket> SaaApplication::cdtiSocket = nullptr;
std::vector<SensorData> planes;
std::mutex mtx;
SensorData ownshipPlane("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);

void acceptNetworkConnection(std::shared_ptr<ServerConnectionManager> mgr)
{
   mgr->accept();
   std::cout << "Server has accepted cdti socket" << std::endl;
}

/**
 * Sets up the socket connections to the test server for reading in sensor data.
 */
void SocketSetup(ClientSocket &radarSock, ClientSocket &tcasSock, ClientSocket &adsbSock, ClientSocket &ownSock)
{
   try
   {
      radarSock.connect("localhost", 5003);
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
   return nullptr;
   //return cdtiSocket;
}

void SaaApplication::setupSockets(int cdtiPort)
{
   cdtiSocket = std::make_shared<ServerSocket>(cdtiPort);
   std::cout << "cdtiSocket initialized" << std::endl;
}

void SaaApplication::initSocks()
{
   //Set up server sockets
   setupSockets(6000);
   this->connectionManager = std::make_shared<ServerConnectionManager>();
   this->connectionManager->init(cdtiSocket);
   std::thread t1(acceptNetworkConnection, connectionManager);
   //std::thread t2(acceptNetworkConnection,&this->validationOut, getCdtiSocket());

   //set up client sockets
   ClientSocket radarSock, tcasSock, adsbSock, ownSock;
   SocketSetup(radarSock, tcasSock, adsbSock, ownSock);
   t1.join();
   //Let the conection manager get any additional conections (like a CDTI)
   connectionManager->monitor();
   //t2.join();
   //socks.pop_back();
   Decision::setTime0(time(0));
   processSensors(ownSock, adsbSock, tcasSock, radarSock);
}

void SaaApplication::shutdown()
{
   connectionManager->shutdown();
}

/**
 * Takes in an adsbReport and the OwnshipReport data and returns the SensorData version of
 * the adsb data converted to relative position to the ownship.
 */
SensorData SaaApplication::adsbToRelative(AdsBReport adsb, OwnshipReport ownship)
{
   std::string tailNumber = adsb.tail_number();
   float positionN = calcDistance(adsb.latitude(), ownship.ownship_longitude(), ownship.ownship_latitude(),
                                  ownship.ownship_longitude()) * (adsb.latitude() < ownship.ownship_latitude()? -1 : 1);
   float positionE = calcDistance(ownship.ownship_latitude(), adsb.longitude(), ownship.ownship_latitude(),
                                  ownship.ownship_longitude()) * (adsb.longitude() < ownship.ownship_longitude()? -1 : 1);
   float positionD = adsb.altitude() - ownship.ownship_altitude();
   float velocityN = fpsToNmph(ownship.north()) - fpsToNmph(adsb.north());
   float velocityE = fpsToNmph(ownship.east()) - fpsToNmph((adsb.east()));
   float velocityD = fpsToNmph(ownship.down()) - fpsToNmph(adsb.down());
   SensorData adsbPlane(tailNumber, positionN, positionE, positionD, velocityN, velocityE, velocityD, Sensor::adsb, adsb.plane_id(), adsb.timestamp());
   return adsbPlane;
}

/**
 * Takes in a TcasReport and the OwnshipReport data and returns the SensorData version of
 * the tcas data converted to relative position to the ownship.
 */
SensorData SaaApplication::tcasToRelative(TcasReport tcas, OwnshipReport ownship)
{
   std::string tailNumber = std::to_string(tcas.id());
   float positionZ = tcas.altitude();
   float horizRange = (float)(sqrt( tcas.range() * tcas.range()- tcas.altitude() * tcas.altitude()));
   // theta = bearing of intruder + heading of ownship
   float theta = (float)(bearingToRadians(tcas.bearing()) + atan2(ownship.north(), ownship.east()));
   float positionE = (float)(horizRange * cos(theta));
   float positionN = (float)(horizRange * sin(theta));
   float velocityN = 0;
   float velocityE = 0;
   float velocityD = 0;
   SensorData tcasPlane(tailNumber, positionN, positionE, positionZ, velocityN, velocityE, velocityD, Sensor::tcas, tcas.plane_id(), 0);
   return tcasPlane;
}

/**
 * Takes in a RadarReport and the OwnshipReport data and returns the SensorData version of
 * the radar data converted to relative position to the ownship.
 */
SensorData SaaApplication::radarToRelative(RadarReport radar, OwnshipReport ownship)
{
   std::string tailNumber = std::to_string(radar.id());
   float positionZ = (float)(radar.range() * sin(-bearingToRadians(radar.elevation())));
   float vertRange = (float)(positionZ / NAUT_MILES_TO_FEET);
   float horizRange = (float)(sqrt(radar.range() * radar.range() - vertRange * vertRange));
   // theta = bearing of intruder + heading of ownship
   float theta = (float)(bearingToRadians(radar.azimuth()) + atan2(ownship.north(), ownship.east()));
   float positionE = (float)(horizRange * cos(theta));
   float positionN = (float)(horizRange * sin(theta));
   float velocityN = fpsToNmph(radar.north());
   float velocityE = fpsToNmph(radar.east());
   float velocityD = fpsToNmph(radar.down());
   SensorData radarPlane(tailNumber, positionN, positionE, positionZ, velocityN, velocityE, velocityD, Sensor::radar, radar.plane_id(), radar.timestamp());
   return radarPlane;
}

/*
 * Thread for the ownship socket data. Reads in an ownship reports and updates the shared ownship data.
 */
void processOwnship(ClientSocket &ownSock, OwnshipReport &ownship, bool &finished)
{
   while(ownSock.hasData())
   {
      ownSock.operator>>(ownship); //blocking call, waits for server
      // TODO: Switch to actual ownship data for use by Decision
      ownshipPlane = SensorData("Ownship", 0, 0, 0, ownship.north(), ownship.east(), ownship.down(), Sensor::ownship, 0, 0);
   }
   std::cout << "Ownship Thread done\n";

   finished = true;
}

/*
 * The thread for the adsb socket data. Reads in a adsb reports and adds them to the shared list of planes.
 */
void processAdsb(ClientSocket &adsbSock, OwnshipReport &ownship, bool &finished)
{
   AdsBReport adsb;
   while(adsbSock.hasData())
   {
      adsbSock.operator>>(adsb); //blocking call, waits for server
      mtx.lock();
      planes.push_back(SaaApplication::adsbToRelative(adsb, ownship));
      mtx.unlock();
   }
   std::cout << "ADSBThread done\n";

   finished = true;
}

/*
 * The thread for the tcas socket data. Reads in a tcas reports and adds them to the shared list of planes.
 */
void processTcas(ClientSocket &tcasSock, OwnshipReport &ownship, bool &finished)
{
   TcasReport tcas;
   while(tcasSock.hasData())
   {
      tcasSock.operator>>(tcas); //blocking call, waits for server
      mtx.lock();
      planes.push_back(SaaApplication::tcasToRelative(tcas, ownship));
      mtx.unlock();
   }
   std::cout << "TCASThread done\n";

   finished = true;
}

/*
 * The thread for the radar socket data. Reads in a radar reports and adds them to the shared list of planes.
 */
void processRadar(ClientSocket &radarSock, OwnshipReport &ownship, bool &finished)
{
   RadarReport radar;
   while(radarSock.hasData())
   {
      radarSock.operator>>(radar); //blocking call, waits for server
      mtx.lock();
      planes.push_back(SaaApplication::radarToRelative(radar, ownship));
      mtx.unlock();
   }
   std::cout << "RadarThread done\n";

   finished = true;
}

/*
 * Sets up the separate threads for the individual plane sensor sockets and contains
 * the main loop for timing when to send data on to the correlation module,
 * then the decision module, and finally onto the cdti and validation server.
 */
void SaaApplication::processSensors(ClientSocket ownSock, ClientSocket adsbSock, ClientSocket tcasSock, ClientSocket radarSock)
{
   Correlation cor;
   Decision dec;
   CDTIReport *rep = nullptr;
   OwnshipReport ownship;

   try
   {
      bool adsbFinished = false, ownshipFinished = false, tcasFinished = false, radarFinished = false;
      CDTIPlane::Severity severity;
      std::thread ownshipthread(processOwnship, std::ref(ownSock), std::ref(ownship), std::ref(ownshipFinished));
      std::thread adsbthread(processAdsb, std::ref(adsbSock), std::ref(ownship), std::ref(adsbFinished));
      std::thread tcasthread(processTcas, std::ref(tcasSock), std::ref(ownship), std::ref(tcasFinished));
      std::thread radarthread(processRadar, std::ref(radarSock), std::ref(ownship), std::ref(radarFinished));

      while (!adsbFinished && !ownshipFinished && !tcasFinished && !radarFinished)
      {
         std::this_thread::sleep_for(std::chrono::seconds(1));
         mtx.lock();
         std::vector<SensorData> planesCopy = planes;
         planes.clear();
         mtx.unlock();
         std::vector<CorrelatedData> planesResult = cor.correlate(planesCopy);
         dec.calcAdvisory(&list, &planesResult, &severity, &ownshipPlane);
         rep = dec.generateReport(&list, ownshipPlane.getCDTIPlane(), &severity);
         connectionManager->sendMessage(*rep);
         //validationOut << (*rep); // send back to validation module
         std::cout << "finished one cycle" << std::endl;
      }

      adsbthread.join();
      tcasthread.join();
      radarthread.join();
      ownshipthread.join();
   }
   catch (SocketException)
   {
      std::cout << "got a socket exception... exiting" << std::endl;
      exit(-1);
   }

   delete rep;
}