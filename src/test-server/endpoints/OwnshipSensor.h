//
// Created by Kyle Piddington on 11/28/15.
//

#ifndef SAA_APPLICATION_OWNSHIPSENSOR_H
#define SAA_APPLICATION_OWNSHIPSENSOR_H
#include "test-server/endpoints/Sensor.h"

class OwnshipSensor : public Sensor {
   public:
   OwnshipSensor(SensorEndpoint * endpoint);
   virtual void sendData(const TestServerPlane & plane);


};


#endif //SAA_APPLICATION_OWNSHIPSENSOR_H
