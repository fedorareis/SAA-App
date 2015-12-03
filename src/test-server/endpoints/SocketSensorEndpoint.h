//
// Created by Kyle Piddington on 11/30/15.
//

#ifndef SAA_APPLICATION_SOCKETSENSORENDPOINT_H
#define SAA_APPLICATION_SOCKETSENSORENDPOINT_H
#include "test-server/endpoints/SensorEndpoint.h"
class SocketSensorEndpoint : public SensorEndpoint
{
   public:
   SocketSensorEndpoint();

   SocketSensorEndpoint(int port);
      ~SocketSensorEndpoint();
      void accept(SensorEndpoint & other);
      SensorEndpoint & operator << (const ::google::protobuf::Message & msg);
   protected:

};
#endif //SAA_APPLICATION_SOCKETSENSORENDPOINT_H
