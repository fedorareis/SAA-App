//
// Created by Kyle Piddington on 11/24/15.
//

#ifndef SAA_APPLICATION_ENDPOINT_H
#define SAA_APPLICATION_ENDPOINT_H
#include "common/sockets/ServerSocket.h"
#include "test-server/Plane.h"
#include "test-server/endpoints/ConnectionInfo.h"

class SensorEndpoint {
   public:
      SensorEndpoint();
      ~SensorEndpoint();
      ServerSocket & getSocket();
   protected:
      ServerSocket socket;


};


#endif //SAA_APPLICATION_ENDPOINT_H
