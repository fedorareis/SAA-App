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
#include <gtest/gtest.h>

/**
 * The RadarSensor transforms standard test data into a radar newtork message
 * And can be used to send
 */
class RadarSensor : public Sensor {
   public:
   RadarSensor(SensorEndpoint * endpoint);
   virtual void sendData(const TestServerPlane &plane, const TestServerPlane & other);

   private:
   static RadarReport createReport(const TestServerPlane & plane, const TestServerPlane & ownship);

   FRIEND_TEST(RadarSensorTest, testBasicReport);
   FRIEND_TEST(RadarSensorTest, testVelocity);
};


#endif
