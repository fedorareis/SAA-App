//
// Created by Kyle Reis on 5/9/16.
//

#include <gtest/gtest.h>
#include <saa-application/TestDecision.h>
#include "saa-application/SensorData.h"
#include "saa-application/CorrelatedData.h"
#include <common/protobuf/cdti.pb.h>

TEST(TestDecisionTest, setSensitivityLevel)
{
   SensorData ownship("Ownship", 0, 0, 42000, 0, 0, 0, Sensor::ownship, 0, 0);
   TestDecision dec;

   //ASSERT_EQ(7 , dec.setSensitivityLevel(&ownship));
   //ownship("Ownship", 0, 0, 42001, 0, 0, 0, Sensor::ownship, 0, 0);
}

TEST(TestDecisionTest, calculateTAUMod)
{
   SensorData ownship("Ownship", 0, 0, 42000, 0, 0, 0, Sensor::ownship, 0, 0);
   CorrelatedData plane(1, 0, 42000, 0, 0, 0);
   TestDecision dec;

   ASSERT_EQ(0, 1);
}