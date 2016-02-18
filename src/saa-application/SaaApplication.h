//
// Created by Kyle Piddington on 11/15/15.
//

#ifndef SAA_APPLICATION_SAAAPPLICATION_H
#define SAA_APPLICATION_SAAAPPLICATION_H

#include <vector>
#include <common/protobuf/cdti.pb.h>
#include <common/protobuf/ownship.pb.h>
#include "common/sockets/ServerSocket.h"
#include "SensorData.h"
#include "ServerConnectionManager.h"

class SaaApplication
{
public:
   void initSocks();
   static ServerSocket * getCdtiSocket();
   static void shutdown();
private:
   static void setupSockets(int CdtiSocket);
   std::vector<CDTIPlane *> list;
   static std::shared_ptr<ServerSocket>  cdtiSocket;
   void processSensors(ClientSocket ownSock, ClientSocket adsbSock, ClientSocket tcasSock, ClientSocket radarSock);
   static std::shared_ptr<ServerConnectionManager> connectionManager;
};
#endif //SAA_APPLICATION_SAAAPPLICATION_H
