//
// Created by Kyle Piddington on 11/30/15.
//

#include "SocketSensorEndpoint.h"
SocketSensorEndpoint::SocketSensorEndpoint(int port):
      SensorEndpoint()

{
   socket = new ServerSocket(port);
}
SocketSensorEndpoint::SocketSensorEndpoint():
   SensorEndpoint()
{
   socket = new ServerSocket();
}

SocketSensorEndpoint::~SocketSensorEndpoint()
{

}



void SocketSensorEndpoint::accept(SensorEndpoint &other) {
   if(other.socket != nullptr)
      delete other.socket;
   other.socket = new ServerSocket();
   this->socket->accept(other.getSocket());
}
