//
// Created by Kyle Piddington on 11/24/15.
//

#include "SensorEndpoint.h"


SensorEndpoint::SensorEndpoint()
{
   socket = ServerSocket();
}
SensorEndpoint::~SensorEndpoint()
{
   socket.close();
}

ServerSocket & SensorEndpoint::getSocket()
{
   return socket;
}