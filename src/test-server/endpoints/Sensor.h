//
// Created by Kyle Piddington on 11/24/15.
//

#ifndef SAA_APPLICATION_SENSOR_H
#define SAA_APPLICATION_SENSOR_H


#include <test-server/endpoints/SensorEndpoint.h>

class Sensor {

   public:
   Sensor(){};
   virtual ~Sensor(){
      if(endpoint != nullptr)
         delete endpoint;
   }
   void close();
   Sensor(SensorEndpoint * endpoint);
   SensorEndpoint & getEndpoint();
   void setEndpoint(SensorEndpoint * endpoint) {this->endpoint = endpoint;}
   private:
   SensorEndpoint * endpoint;
   virtual void sendData(const TestServerPlane & plane) = 0;
};


#endif //SAA_APPLICATION_SENSOR_H
