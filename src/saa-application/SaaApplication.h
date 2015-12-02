//
// Created by Kyle Piddington on 11/15/15.
//

#ifndef SAA_APPLICATION_SAAAPPLICATION_H
#define SAA_APPLICATION_SAAAPPLICATION_H

#include <vector>
#include <common/protobuf/cdti.pb.h>
#include "common/sockets/ServerSocket.h"

class SaaApplication
{
public:
   void report();
   static ServerSocket * getCdtiSocket();
   static void setupSockets(int CdtiSocket);
private:
   std::vector<CDTIPlane *> list;
   static ServerSocket * cdtiSocket;
   ServerSocket cdtiOut;
   ServerSocket validationOut;
};
#endif //SAA_APPLICATION_SAAAPPLICATION_H
