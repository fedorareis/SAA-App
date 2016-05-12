//
// Created by Kyle Reis on 5/11/16.
//

#include <gtest/gtest.h>
#include "saa-application/SensorData.h"
#include <common/protobuf/cdti.pb.h>

TEST(TestSensorData, position)
{
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   ASSERT_EQ(Vector3d(0,0,0), ownship.getPurePosition());

   ownship.supersedePosition(0, 0, 1);
   ASSERT_EQ(Vector3d(0,0,1), ownship.getPurePosition());

   ownship.supersedePosition(5000, -200, 0.543454454);
   ASSERT_EQ(5000, ownship.getPurePosition().x);
   ASSERT_EQ(-200, ownship.getPurePosition().y);
   ASSERT_EQ(0.543454454, ownship.getPurePosition().z);
}

TEST(TestSensorData, positionComplex)
{
   SensorData ownship("Ownship", 5000, -200, 0.543454454, 0, 0, 0, Sensor::ownship, 0, 0);
   ASSERT_EQ(5000, ownship.getPurePosition().x);
   ASSERT_EQ(-200, ownship.getPurePosition().y);
   ASSERT_EQ(0.543454454, ownship.getPurePosition().z);
}