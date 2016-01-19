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
#include "Plane.h"
#include "common/Maths.h"


ServerSocket *SaaApplication::cdtiSocket = nullptr;
std::vector<Plane> planes;
std::mutex mtx;

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

void SaaApplication::convertOwnship(OwnshipReport ownship)
{
   Plane ownshipPlane("Ownship", 0, 0, 0, 0, 0, 0);
   cdtiOwnship = ownshipPlane.getCDTIPlane();
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

void SaaApplication::processSensors(ClientSocket ownSock, ClientSocket adsbSock)
{
   Correlation cor;
   Decision dec;
   CDTIReport *rep = nullptr;
   OwnshipReport ownship;

   try
   {
      std::thread adsb(adsbThread, adsbSock, ownship);
      std::thread ownship(ownshipThread, ownSock, ownship);
      SaaApplication::convertOwnship(ownship);
      planes = cor.correlate(planes);
      //Plane rPlane = planes.back();
      //rPlane.printPos();
      //send to decision making module here
      dec.report(&list, &planes);
      rep = dec.generateReport(&list, cdtiOwnship);
      cdtiOut << (*rep);
      //validationOut << (*rep);
      std::cout << "finished one cycle" << std::endl;
   }
   catch (SocketException)
   {
      std::cout << "got a socket exception..." << std::endl;
      //run = false;
      exit(-1);
   }

   delete rep;
}

void ownshipThread(ClientSocket ownSock, OwnshipReport &ownship)
{
   ownSock.operator>>(ownship); //blocking call, waits for server
}

void adsbThread(ClientSocket adsbSock, OwnshipReport &ownship)
{
   AdsBReport adsb;
   adsbSock.operator>>(adsb); //blocking call, waits for server
   mtx.lock();
   planes.push_back(adsbToRelative(adsb, ownship));
   mtx.unlock();
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