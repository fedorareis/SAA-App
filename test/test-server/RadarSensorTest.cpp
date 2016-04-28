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

   ASSERT_FLOAT_EQ(6.0038409,report.range());
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
