//
// Created by Kyle Piddington on 11/24/15.
//

#ifndef SAA_APPLICATION_SENSOR_H
#define SAA_APPLICATION_SENSOR_H


#include <test-server/endpoints/SensorEndpoint.h>

class Sensor {

   public:
   SensorEndpoint & getEndpoint();
   private:
   SensorEndpoint endpoint;
   virtual void sendData(Plane & plane) = 0;
};


#endif //SAA_APPLICATION_SENSOR_H
