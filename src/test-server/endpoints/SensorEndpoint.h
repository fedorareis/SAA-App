//
// Created by Kyle Piddington on 11/24/15.
//

#ifndef SAA_APPLICATION_ENDPOINT_H
#define SAA_APPLICATION_ENDPOINT_H
#include "common/sockets/ServerSocket.h"
#include "test-server/planes/TestServerPlane.h"
#include "test-server/endpoints/ConnectionInfo.h"

class SensorEndpoint {
   public:
      SensorEndpoint();
      virtual  ~SensorEndpoint();
      virtual void accept(SensorEndpoint & endpoint) = 0;
      virtual void close();

      ServerSocket & getSocket();

      //please don't use this i'm horrible ~love kyle
      ServerSocket * socket;


};


#endif //SAA_APPLICATION_ENDPOINT_H
