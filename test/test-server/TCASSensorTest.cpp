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
   plane.setLatLongAlt(Vector3d(50.1,0,2000 + NAUT_MILES_TO_FEET));
   TcasSensor sensor(nullptr, false);
   TcasReport report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(NAUT_MILES_TO_FEET,report.altitude());
   ASSERT_FLOAT_EQ(0,report.bearing());
   ASSERT_FLOAT_EQ(6.0865512,report.range());

   ownship.setNorthEastDownVelocity(Vector3d(0,1,0));
   report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(-90,report.bearing());

   ownship.setNorthEastDownVelocity(Vector3d(1,-1,0));
   report = sensor.createReport(plane,ownship);
   ASSERT_FLOAT_EQ(45,report.bearing());

}