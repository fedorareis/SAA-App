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


#ifndef SAA_APPLICATION_SAAAPPLICATION_H
#define SAA_APPLICATION_SAAAPPLICATION_H

#include <vector>
#include <common/protobuf/cdti.pb.h>
#include <common/protobuf/ownship.pb.h>
#include <common/protobuf/adsb.pb.h>
#include <common/protobuf/tcas.pb.h>
#include <common/protobuf/radar.pb.h>
#include "common/sockets/ServerSocket.h"
#include "SensorData.h"
#include "ServerConnectionManager.h"

class SaaApplication
{
public:
   void initSocks();
   static ServerSocket * getCdtiSocket();
   static void shutdown();

   /**
    * These three functions take in a sensor report and the OwnshipReport data and
    * returns the SensorData version of the data converted to relative position to the ownship.
    */
   static SensorData adsbToRelative(AdsBReport adsb, OwnshipReport ownship);
   static SensorData tcasToRelative(TcasReport tcas, OwnshipReport ownship);
   static SensorData radarToRelative(RadarReport radar, OwnshipReport ownship);
private:
   static void setupSockets(int CdtiSocket);
   static std::shared_ptr<ServerSocket>  cdtiSocket;
   void processSensors(ClientSocket ownSock, ClientSocket adsbSock, ClientSocket tcasSock, ClientSocket radarSock);
   static std::shared_ptr<ServerConnectionManager> connectionManager;
};
#endif //SAA_APPLICATION_SAAAPPLICATION_H
