//
// Created by Kyle Piddington on 11/28/15.
//

#ifndef SAA_APPLICATION_ADSBSENSOR_H
#define SAA_APPLICATION_ADSBSENSOR_H

#include "Sensor.h"

class AdsbSensor : public Sensor {
   public:
   AdsbSensor(SensorEndpoint * endpoint,bool jitter = false);
   virtual void sendData(const TestServerPlane & plane, const TestServerPlane & ownship) override;

};


#endif //SAA_APPLICATION_ADSBSENSOR_H
