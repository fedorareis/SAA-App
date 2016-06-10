/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
/*
 * Created by Kyle Piddington on 11/15/15.
 * Main Author: Jacob Hardi
 *
 * This module is where the main connections between the test server and CDTI happen.
 * It takes in the data from the test server and passes it to the correlation module,
 * then to the decision module, and then onto the CDTI as well as back to the test
 * server for validation.
 */

#include <iostream>
#include <vector>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include <common/protobuf/adsb.pb.h>
#include "SaaApplication.h"
#include "MeanShiftCorrelation.h"
#include "KMeansCorrelation.h"
#include "Decision.h"
#include "ServerConnectionManager.h"
#include "HiercClusteringCorrelation.h"
#include <mutex>
#include <common/protobuf/tcas.pb.h>
#include <common/protobuf/radar.pb.h>
#include <common/FrameBody.h>


std::shared_ptr<ServerConnectionManager> SaaApplication::connectionManager = nullptr;
std::shared_ptr<ServerSocket> SaaApplication::cdtiSocket = nullptr;
std::vector<SensorData> planes;
std::mutex planeMutex;
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
                                  ownship.ownship_longitude(), ownship.ownship_altitude() * FEET_TO_NAUT_MILES) * (adsb.latitude() < ownship.ownship_latitude()? -1 : 1);
   float positionE = calcDistance(ownship.ownship_latitude(), adsb.longitude(), ownship.ownship_latitude(),
                                  ownship.ownship_longitude(), ownship.ownship_altitude() * FEET_TO_NAUT_MILES) *
       (adsb.longitude() <
       ownship.ownship_longitude()? -1 : 1);
   float positionD = ownship.ownship_altitude() - adsb.altitude();
   float velocityN = fpsToNmph(ownship.north()) - fpsToNmph(adsb.north());
   float velocityE = fpsToNmph(ownship.east()) - fpsToNmph((adsb.east()));
   float velocityD = fpsToNmph(ownship.down()) - fpsToNmph(adsb.down());
   SensorData adsbPlane(tailNumber, positionN, positionE, positionD, adsb.north(), adsb.east(), adsb.down
       (), Sensor::adsb, adsb
       .plane_id(), adsb
       .timestamp());
   return adsbPlane;
}

/**
 * Takes in a TcasReport and the OwnshipReport data and returns the SensorData version of
 * the tcas data converted to relative position to the ownship.
 */
SensorData SaaApplication::tcasToRelative(TcasReport tcas, OwnshipReport ownship)
{
   std::string tailNumber = std::string("TCAS" + std::to_string(tcas.plane_id()));
   float positionZ = tcas.altitude();
   float horizRange = tcas.range();
   // ownship_compass_bearing = bearing of intruder + heading of ownship
   float ownship_compass_bearing = (float) degToRad(tcas.bearing());
   //std::cout << ownship_compass_bearing << std::endl;
   //std::cout << horizRange << std::endl;
   float positionN = (float)(horizRange * cos(ownship_compass_bearing));
   float positionE = (float)(horizRange * sin(ownship_compass_bearing));
   float velocityN = 0;
   float velocityE = 0;
   float velocityD = 0;
   SensorData tcasPlane(tailNumber, positionN, positionE, positionZ, velocityN, velocityE, velocityD, Sensor::tcas, tcas.plane_id(), 0);
//   std::cout << "show tcas " << tcas.plane_id() << " pos" << std::endl;
//   tcasPlane.printPos();
   //std::cout << tcas.range << std::endl;
   return tcasPlane;
}

/**
 * Takes in a RadarReport and the OwnshipReport data and returns the SensorData version of
 * the radar data converted to relative position to the ownship.
 */
SensorData SaaApplication::radarToRelative(RadarReport radar, OwnshipReport ownship)
{
//   std::cout << radar.DebugString() << std::endl;

   std::string tailNumber = std::string("RDR" + std::to_string(radar.plane_id()));
   double range = radar.range() * FEET_TO_NAUT_MILES; // converts range from feet to Nautical Miles
   double elv = degToRad(radar.elevation());
   double azm = degToRad(radar.azimuth());
   float z = range * sin(-elv);
//   float vertRange = (float)(z / FEET_TO_NAUT_MILES);
   float horizRange = range * cos(-elv);
   // theta = bearing of intruder + heading of ownship
   float x = horizRange * cos(azm);
   float y = horizRange * sin(azm);

   Vector3d ownshiplla(radar.latitude(),radar.longitude(), radar.altitude() * FEET_TO_NAUT_MILES);
   Vector3d planeVel(radar.north() * FEET_TO_NAUT_MILES, radar.east() * FEET_TO_NAUT_MILES, radar.down() *
       FEET_TO_NAUT_MILES);
   Vector3d ownshipVel(ownship.north() * FEET_TO_NAUT_MILES, ownship.east()* FEET_TO_NAUT_MILES, ownship.down()*
       FEET_TO_NAUT_MILES);
   FrameBody ownFrameB(ownshiplla, makeBodyBasis(ownshiplla,ownshipVel));
   Vector3d P_EO_E = ownFrameB.utx(Vector3d(x,y,z));
   auto lla = xyzToLla(P_EO_E);
//   std::cout << "plane lla radar " << lla << std::endl;
//   float R = (float)P_EO_E.getMagnitude();

   float positionN = calcDistance(lla.latitude(), ownship.ownship_longitude(), ownship.ownship_latitude(),
                                  ownship.ownship_longitude(), ownship.ownship_altitude()) * (lla.latitude() < ownship
       .ownship_latitude()? -1 : 1);
   float positionE = calcDistance(ownship.ownship_latitude(), lla.longitude(), ownship.ownship_latitude(),
                                  ownship.ownship_longitude(), ownship.ownship_altitude()) * (lla.longitude() <
       ownship.ownship_longitude()? -1 : 1);

   float positionD = (float) ownshiplla.z - lla.z;

   SensorData radarPlane(tailNumber, positionN, positionE, positionD, planeVel.x, planeVel.y, planeVel.z,
                         Sensor::radar, radar.plane_id(), radar.timestamp());
//   std::cout  << "sensor data:  ";
//   radarPlane.printPos();
//   std::cout << std::endl;
   return radarPlane;
}

/*
 * Thread for the ownship socket data. Reads in an ownship reports and updates the shared ownship data.
 */
void processOwnship(ClientSocket &ownSock, OwnshipReport &ownship, bool &finished)
{
   while(ownSock.hasData())
   {
      planeMutex.lock();
      // blocking call, waits for server
      ownSock.operator>>(ownship);
      // TODO: Switch to actual ownship data for use by Decision
      ownshipPlane = SensorData("Ownship", ownship.ownship_latitude(),
                                ownship.ownship_longitude(),
                                ownship.ownship_altitude(),
                                ownship.north(), ownship.east(),
                                ownship.down(), Sensor::ownship, 0, 0);
      planeMutex.unlock();
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

   while (adsbSock.hasData())
   {
      adsbSock.operator>>(adsb); //blocking call, waits for server
      planeMutex.lock();
      AdsBReport *cpy = new AdsBReport;
      cpy->CopyFrom(adsb);
      planes.push_back(SaaApplication::adsbToRelative(*cpy, ownship));
      planeMutex.unlock();
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

   while (tcasSock.hasData())
   {
      tcasSock.operator>>(tcas); //blocking call, waits for server
      planeMutex.lock();
      planes.push_back(SaaApplication::tcasToRelative(tcas, ownship));
      //planes.back().printPos();
      planeMutex.unlock();
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

   while (radarSock.hasData())
   {
      radar.Clear();
      radarSock.operator>>(radar); //blocking call, waits for server
      planeMutex.lock();
      RadarReport* cpy = new RadarReport;
      cpy->CopyFrom(radar);
      planes.push_back(SaaApplication::radarToRelative(*cpy, ownship));
      //planes.back().printPos();
      planeMutex.unlock();
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
   std::shared_ptr<CorrelationStrategy> cor = std::shared_ptr<CorrelationStrategy>(new MeanShiftCorrelation());
   Decision dec;
   CDTIReport *rep = nullptr;
   OwnshipReport ownship;

   try
   {
      bool adsbFinished = false, ownshipFinished = false, tcasFinished = false, radarFinished = false;

      std::thread ownshipthread(processOwnship, std::ref(ownSock), std::ref(ownship), std::ref(ownshipFinished));
      std::thread adsbthread(processAdsb, std::ref(adsbSock), std::ref(ownship), std::ref(adsbFinished));
      std::thread tcasthread(processTcas, std::ref(tcasSock), std::ref(ownship), std::ref(tcasFinished));
      std::thread radarthread(processRadar, std::ref(radarSock), std::ref(ownship), std::ref(radarFinished));

      /*
       * This is the main loop that runs once per second, data that was collected over the last cycle is
       * sent to the correlation module and then onto the decision module before being sent onto the CDTI
       * and back to the test server.
       */
      while (!adsbFinished && !ownshipFinished && !tcasFinished && !radarFinished)
      {
         std::this_thread::sleep_for(std::chrono::seconds(1));
         planeMutex.lock();
         std::vector<SensorData> planesCopy = planes;
         planes.clear();
         ownshipPlane = SensorData("Ownship", 0, 0, 0, ownship.north(), ownship.east(), ownship.down(), Sensor::ownship, 0, 0);
         std::vector<CorrelatedData> planesResult = cor->correlate(planesCopy);
         rep = dec.calcAdvisory(&planesResult, &ownshipPlane);
         connectionManager->sendMessage(*rep);
         planeMutex.unlock();

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