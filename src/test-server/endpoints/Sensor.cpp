//
// Created by Kyle Piddington on 11/24/15.
//

#include "Sensor.h"

SensorEndpoint & Sensor::getEndpoint()
{
   return *endpoint;
}

Sensor::Sensor(SensorEndpoint *endpoint):
      endpoint(endpoint)
{

}

void Sensor::close() {
   endpoint->close();
}
