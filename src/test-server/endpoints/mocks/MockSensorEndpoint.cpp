//
// Created by Kyle Piddington on 11/30/15.
//

#include <common/sockets/mocks/MockServerSocket.h>
#include "MockSensorEndpoint.h"

MockSensorEndpoint::MockSensorEndpoint() :
SensorEndpoint()
{
   this->socket = new MockServerSocket();
}

MockSensorEndpoint::~MockSensorEndpoint() {

}

void MockSensorEndpoint::accept(SensorEndpoint &endpoint) {
   if(endpoint.socket != nullptr)
      delete endpoint.socket;
   endpoint.socket = new MockServerSocket();
}
//Does nothing on a mock endpoint
void MockSensorEndpoint::close() {

}
