//
// Created by Kyle Piddington on 11/24/15.
//

#include <common/sockets/SocketException.h>
#include "SensorEndpoint.h"


SensorEndpoint::SensorEndpoint():
socket(nullptr)
{

}
SensorEndpoint::~SensorEndpoint()
{
   if(socket != nullptr)
      delete socket;
}

ServerSocket &SensorEndpoint::getSocket() {
   if(socket == nullptr)
   {
      throw SocketException("This sensor endpoint does not actually have a socket. huh, go figure");
   }
   return *socket;

}
