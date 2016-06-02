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

#include <gtest/gtest.h>
#include <common/Maths.h>
#include <test-server/planes/TestServerPlane.h>
#include "common/protobuf/tcas.pb.h"
#include <test-server/endpoints/TcasSensor.h>
TEST(TCAS,createTcasMessage)
{
   TestServerPlane plane;
   TestServerPlane ownship;
   TcasSensor sensor(nullptr, false);
   ownship.setNorthEastDownVelocity(Vector3d(1,0,0));
   ownship.setLatLongAlt(Vector3d(50,0,2000));
   plane.setLatLongAlt(Vector3d(50.1,0,2000));

   TcasReport report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(0,report.bearing());
   ASSERT_FLOAT_EQ(6.0038409,report.range());

   ownship.setNorthEastDownVelocity(Vector3d(0,1,0));
   report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(-90,report.bearing());

   ownship.setNorthEastDownVelocity(Vector3d(1,-1,0));
   report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(45,report.bearing());

}

TEST(TCAS,testAltitudeDistance)
{
   TestServerPlane plane;
   TestServerPlane ownship;
   ownship.setNorthEastDownVelocity(Vector3d(1,0,0));
   ownship.setLatLongAlt(Vector3d(50,0,2000));
   plane.setLatLongAlt(Vector3d(50.1,0, 2000 + FEET_TO_NAUT_MILES));
   TcasSensor sensor(nullptr, false);
   TcasReport report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(FEET_TO_NAUT_MILES, report.altitude());
   ASSERT_FLOAT_EQ(0,report.bearing());
   ASSERT_FLOAT_EQ(6.0865512,report.range());

   ownship.setNorthEastDownVelocity(Vector3d(0,1,0));
   report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(-90,report.bearing());

   ownship.setNorthEastDownVelocity(Vector3d(1,-1,0));
   report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(45,report.bearing());

}