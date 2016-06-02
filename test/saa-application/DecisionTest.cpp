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
// Created by Kyle Reis on 3/2/16.
//

#include <gtest/gtest.h>
#include <saa-application/Decision.h>
#include "saa-application/SensorData.h"
#include "saa-application/CorrelatedData.h"
#include <common/protobuf/cdti.pb.h>

CorrelatedData plane1(50, 50, 5000, 100, 100, 0);
CorrelatedData plane2(9, 0, 900, 100, 100, 0);
CorrelatedData plane3(4, 0, 0, -10, 0, 0);
CorrelatedData plane4(1, 0, 0, -10, 0, 0);
CorrelatedData plane5(0, 0, 0, 0, 0, 0);

TEST(DecisionTest, testCalAdvisoryAir)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // AIR
   std::cout << "AIR TEST" << std::endl;
   planes.push_back(plane1);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIPlane::AIR, result->planes().Get(0).severity());
   ASSERT_EQ(CDTIReport::AIR, result->advisorylevel());
}

TEST(DecisionTest, testCalAdvisoryProximate)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Proximate
   std::cout << "PROXIMATE TEST" << std::endl;
   planes.push_back(plane2);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIPlane::PROXIMATE, result->planes().Get(0).severity());
   ASSERT_EQ(CDTIReport::PROXIMATE, result->advisorylevel());
}

TEST(DecisionTest, testCalAdvisoryTraffic)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Traffic
   std::cout << "TRAFFIC TEST" << std::endl;
   planes.push_back(plane3);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIPlane::TRAFFIC, result->planes().Get(0).severity());
   ASSERT_EQ(CDTIReport::TRAFFIC, result->advisorylevel());
}

TEST(DecisionTest, testCalAdvisoryResolution)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Resolution
   std::cout << "RESOLUTION TEST" << std::endl;
   planes.push_back(plane4);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIPlane::RESOLUTION, result->planes().Get(0).severity());
   ASSERT_EQ(CDTIReport::RESOLUTION, result->advisorylevel());
}

TEST(DecisionTest, testCalAdvisoryCrash)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Crash
   std::cout << "CRASH TEST" << std::endl;
   planes.push_back(plane5);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIPlane::CRASH, result->planes().Get(0).severity());
   ASSERT_EQ(CDTIReport::CRASH, result->advisorylevel());
}

// Tests that if there are multiple planes and the highest severity is CRASH then the Report has severity CRASH
TEST(DecisionTest, testCalAdvisoryMultiCrash)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Crash
   std::cout << "MULTI-PLANE CRASH TEST" << std::endl;
   planes.push_back(plane4);
   planes.push_back(plane2);
   planes.push_back(plane5);
   planes.push_back(plane1);
   planes.push_back(plane3);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIReport::CRASH, result->advisorylevel());
}

// Tests that if there are multiple planes and the highest severity is RESOLUTION then the Report has severity RESOLUTION
/*TEST(DecisionTest, testCalAdvisoryMultiResolution)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Crash
   std::cout << "MULTI-PLANE RESOLUTION TEST" << std::endl;
   planes.push_back(plane2);
   planes.push_back(plane4);
   planes.push_back(plane1);
   planes.push_back(plane3);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIReport::RESOLUTION, result->advisorylevel());
}

// Tests that if there are multiple planes and the highest severity is TRAFFIC then the Report has severity TRAFFIC
TEST(DecisionTest, testCalAdvisoryMultiTraffic)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Crash
   std::cout << "MULTI-PLANE TRAFFIC TEST" << std::endl;
   planes.push_back(plane2);
   planes.push_back(plane3);
   planes.push_back(plane1);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIReport::TRAFFIC, result->advisorylevel());
}

// Tests that if there are multiple planes and the highest severity is PROXIMATE then the Report has severity CRASH
TEST(DecisionTest, testCalAdvisoryMultiProximate)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Crash
   std::cout << "MULTI-PLANE PROXIMATE TEST" << std::endl;
   planes.push_back(plane1);
   planes.push_back(plane2);
   planes.push_back(plane1);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIReport::PROXIMATE, result->advisorylevel());
}

// Tests that if there are multiple planes and the highest severity is AIR then the Report has severity AIR
TEST(DecisionTest, testCalAdvisoryMultiAir)
{
   std::vector<CorrelatedData> planes;
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   Decision dec;
   CDTIReport *result;

   // Crash
   std::cout << "MULTI-PLANE AIR TEST" << std::endl;
   planes.push_back(plane1);
   planes.push_back(plane1);
   planes.push_back(plane1);
   result = dec.calcAdvisory(&planes, &ownship);
   ASSERT_EQ(CDTIReport::AIR, result->advisorylevel());
}*/