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
