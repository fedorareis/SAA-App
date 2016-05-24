//
// Created by Kyle Piddington on 11/24/15.
//


#include <iostream>
#include "Sensor.h"

SensorEndpoint & Sensor::getEndpoint()
{
   return *endpoint;
}

Sensor::Sensor(SensorEndpoint *endpoint, bool jitter):
      endpoint(endpoint),
      jitter(jitter)
{

}

void Sensor::close() {
   if(endpoint != nullptr)
   {
      endpoint->close();
   }

}

void Sensor::setJitter(bool jitter) {
   std::cout << "Jitter set to " << jitter << std::endl;

   this->jitter = jitter;
}
