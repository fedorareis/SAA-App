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
// Created by Kyle Piddington on 2/2/16.
//

#include <gtest/gtest.h>
#include <test-server/planes/TestServerPlane.h>
#include <common/Maths.h>
#include <test-server/endpoints/RadarSensor.h>
#include <common/TestVec3dNoise.h>

TEST(RadarSensorTest, testBasicReport)
{
   TestServerPlane plane;
   TestServerPlane ownship;
   RadarSensor sensor(nullptr,false);
   ownship.setNorthEastDownVelocity(Vector3d(1,0,0));
   ownship.setLatLongAlt(Vector3d(50,0,2000));
   plane.setLatLongAlt(Vector3d(50.1,0,2000));

   RadarReport report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(0,report.azimuth());

   ASSERT_FLOAT_EQ(6.0038409 * FEET_TO_NAUT_MILES,report.range());
   ASSERT_FLOAT_EQ(0,report.elevation());

   ownship.setNorthEastDownVelocity(Vector3d(0,1,0));
   report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(-90,report.azimuth());
   ASSERT_FLOAT_EQ(0,report.elevation());


   ownship.setNorthEastDownVelocity(Vector3d(1,-1,0));
   report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(45,report.azimuth());
   ASSERT_FLOAT_EQ(0, report.elevation());


}

TEST(RadarSensorTest, testVelocity)
{
   TestServerPlane plane;
   TestServerPlane ownship;
   RadarSensor sensor(nullptr, false);
   ownship.setNorthEastDownVelocity(Vector3d(1,0,0));
   ownship.setLatLongAlt(Vector3d(50,0,2000));
   plane.setLatLongAlt(Vector3d(50.1,0,2000));
   RadarReport rept = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(-1,rept.north());
   ASSERT_FLOAT_EQ(0,rept.east());
   ASSERT_FLOAT_EQ(0,rept.down());
   plane.setNorthEastDownVelocity(Vector3d(1,2,3));
   rept = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(0,rept.north());
   ASSERT_FLOAT_EQ(2,rept.east());
   ASSERT_FLOAT_EQ(3,rept.down());
}

TEST(RadarSensorTest, testElevation)
{
   TestServerPlane plane;
   TestServerPlane ownship;
   RadarSensor sensor(nullptr,false);
   ownship.setNorthEastDownVelocity(Vector3d(1,0,0));
   ownship.setLatLongAlt(Vector3d(50,0,2000));
   plane.setLatLongAlt(Vector3d(50.1,0, 2000 + FEET_TO_NAUT_MILES));
   RadarReport rept = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(9.3301497, rept.elevation());
   plane.setLatLongAlt(Vector3d(50.1,0, 2000 - FEET_TO_NAUT_MILES));
   rept = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(-9.3301497, rept.elevation());

}

TEST(RadarSensorTest, testNoise)
{
   TestServerPlane plane;
   TestServerPlane ownship;
   TestVec3dNoise testNoise(Vector3d(1,1,1));
   RadarSensor sensor(nullptr,true);
   ownship.setNorthEastDownVelocity(Vector3d(1,0,0));
   ownship.setLatLongAlt(Vector3d(50,0,2000));
   plane.setLatLongAlt(Vector3d(50.1,0, 2000 + FEET_TO_NAUT_MILES));
   RadarReport rept = sensor.createReport(plane,ownship, testNoise, testNoise);
   ASSERT_FLOAT_EQ(8.0451717, rept.elevation());

   ownship.setNorthEastDownVelocity(Vector3d(1,0,0));
   ownship.setLatLongAlt(Vector3d(50,0,2000));
   plane.setLatLongAlt(Vector3d(50.1,0,2000));
   rept = sensor.createReport(plane,ownship, testNoise, testNoise);
   ASSERT_FLOAT_EQ(0,rept.north());
   ASSERT_FLOAT_EQ(1,rept.east());
   ASSERT_FLOAT_EQ(1,rept.down());

   ownship.setLatLongAlt(Vector3d(50,0,2000));
   plane.setLatLongAlt(Vector3d(50.1,0,2000));
   ownship.setNorthEastDownVelocity(Vector3d(1,-1,0));
   rept = sensor.createReport(plane,ownship, testNoise, testNoise);
   ASSERT_FLOAT_EQ(46,rept.azimuth());
   //1 foot difference is ~ zero
   ASSERT_FLOAT_EQ(0, rept.elevation());
}
