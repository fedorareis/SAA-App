//
// Created by Kyle Reis on 3/2/16.
//

#include <gtest/gtest.h>
#include <saa-application/Decision.h>
#include "saa-application/SensorData.h"
#include "saa-application/CorrelatedData.h"
#include <common/protobuf/cdti.pb.h>

TEST(DecisionTest, testCalAdvisory)
{
   std::vector<CDTIPlane *> list;
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;


   dec.calcAdvisory(&list, &planes, &ownship);

   ASSERT_EQ(0, 1);
}