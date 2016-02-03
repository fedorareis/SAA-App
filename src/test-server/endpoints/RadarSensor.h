//
// Created by Kyle Piddington on 1/26/16.
//

#ifndef SAA_APPLICATION_RADAR_SENSOR
#define SAA_APPLICATION_RADAR_SENSOR

#include <test-server/planes/TestServerPlane.h>
#include <common/protobuf/radar.pb.h>
#include "common/protobuf/tcas.pb.h"
#include "SensorEndpoint.h"
#include "Sensor.h"

class RadarSensor : public Sensor {
   public:
   RadarSensor(SensorEndpoint * endpoint);
   static RadarReport createReport(const TestServerPlane & plane, const TestServerPlane & ownship);

   private:
   virtual void sendData(const TestServerPlane &plane, const TestServerPlane & other);

};


#endif
