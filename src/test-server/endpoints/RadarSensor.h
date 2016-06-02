/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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
#include "common/TestVec3dNoise.h"

/**
 * The RadarSensor transforms standard test data into a radar newtork message
 * And can be used to send
 */
class RadarSensor : public Sensor {
   public:
    RadarSensor(SensorEndpoint *endpoint, bool jitter = false);
   virtual void sendData(const TestServerPlane &plane, const TestServerPlane & other);

   private:
    RadarReport createReport(const TestServerPlane &plane, const TestServerPlane &ownship);
    RadarReport createReport(const TestServerPlane &plane, const TestServerPlane &ownship,
                             Vec3dNoise & radarPosNoise, Vec3dNoise & radarVelNoise);

   FRIEND_TEST(RadarSensorTest, testBasicReport);
   FRIEND_TEST(RadarSensorTest, testVelocity);
   FRIEND_TEST(RadarSensorTest, testElevation);
   FRIEND_TEST(RadarSensorTest, testNoise);
};


#endif
