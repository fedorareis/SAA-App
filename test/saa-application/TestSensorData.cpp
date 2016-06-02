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

   ownship.supersedePosition(5000, -200, 0.5434544);
   ASSERT_EQ(5000, ownship.getPurePosition().x);
   ASSERT_EQ(-200, ownship.getPurePosition().y);
   ASSERT_EQ(((float)0.5434544), ownship.getPurePosition().z);
}

TEST(TestSensorData, velocity)
{
   SensorData ownship("Ownship", 0, 0, 0, 0, 0, 0, Sensor::ownship, 0, 0);
   ASSERT_EQ(Vector3d(0,0,0), ownship.getVelocity());

   ownship.supersedeVelocity(0, 0, 1);
   ASSERT_EQ(Vector3d(0,0,1), ownship.getVelocity());

   ownship.supersedeVelocity(5000, -200, 0.5434544);
   ASSERT_EQ(5000, ownship.getVelocity().x);
   ASSERT_EQ(-200, ownship.getVelocity().y);
   ASSERT_EQ(((float)0.5434544), ownship.getVelocity().z);
}