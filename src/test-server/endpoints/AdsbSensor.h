//
// Created by Kyle Piddington on 11/28/15.
//

#ifndef SAA_APPLICATION_ADSBSENSOR_H
#define SAA_APPLICATION_ADSBSENSOR_H

#include "Sensor.h"
class AdsbSensor : public Sensor {
   public:
   AdsbSensor();
   virtual void sendData(Plane & plane);

};


#endif //SAA_APPLICATION_ADSBSENSOR_H
