//
// Created by Kyle Piddington on 11/15/15.
//

#ifndef SAA_APPLICATION_SAAAPPLICATION_H
#define SAA_APPLICATION_SAAAPPLICATION_H

#include <vector>
#include <common/protobuf/cdti.pb.h>
#include <common/protobuf/ownship.pb.h>
#include "common/sockets/ServerSocket.h"
#include "Plane.h"

class SaaApplication
{
public:
   void initSocks();
   static ServerSocket * getCdtiSocket();
   static void shutdown();
private:
   static void setupSockets(int CdtiSocket);
   void convertOwnship(OwnshipReport ownship);
   std::vector<CDTIPlane *> list;
   static ServerSocket * cdtiSocket;
   void processSensors(ClientSocket ownSock, ClientSocket adsbSocks);
   ServerSocket cdtiOut;
   ServerSocket validationOut;
   CDTIPlane* cdtiOwnship;
};
#endif //SAA_APPLICATION_SAAAPPLICATION_H
