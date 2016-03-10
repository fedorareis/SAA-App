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
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CorrelatedData plane1(50, 10, 5000, 100, 100, 0);
   planes.push_back(plane1);
   CDTIReport* result = dec.calcAdvisory(&planes, &ownship);

   // TODO: switch to AIR once AIR is implemented in proto
   ASSERT_EQ(result->planes().Get(0).severity(), CDTIPlane::PROXIMATE);
   ASSERT_EQ(result->advisorylevel(), CDTIReport::PROXIMATE);

   // Proximate
   CorrelatedData plane2(9, 0, 900, 100, 100, 0);
   planes.push_back(plane2);
   ASSERT_EQ(result->planes().Get(0).severity(), CDTIPlane::PROXIMATE);
   ASSERT_EQ(result->advisorylevel(), CDTIReport::PROXIMATE);

   // Traffic
   CorrelatedData plane3(4, 0, 0, -10, 0, 0);
   planes.push_back(plane3);
   ASSERT_EQ(result->planes().Get(0).severity(), CDTIPlane::TRAFFIC);
   ASSERT_EQ(result->advisorylevel(), CDTIReport::TRAFFIC);

   // Resolution
   CorrelatedData plane4(1, 0, 0, -10, 0, 0);
   planes.push_back(plane4);
   ASSERT_EQ(result->planes().Get(0).severity(), CDTIPlane::RESOLUTION);
   ASSERT_EQ(result->advisorylevel(), CDTIReport::RESOLUTION);

   // Crash TODO: switch to CRASH once CRASH is implemented in proto
   CorrelatedData plane5(.4, 0, 0, -10, 0, 0);
   planes.push_back(plane5);
   ASSERT_EQ(result->planes().Get(0).severity(), CDTIPlane::RESOLUTION);
   ASSERT_EQ(result->advisorylevel(), CDTIReport::RESOLUTION);
}