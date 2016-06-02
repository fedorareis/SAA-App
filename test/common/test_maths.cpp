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
// Created by Kyle Piddington on 1/12/16.
//
#include <gtest/gtest.h>
#include "common/Maths.h"
TEST(Math, fpsToNmph)
{
   EXPECT_FLOAT_EQ(180*KNOT_CONVERSION, fpsToNmph(180));
}

TEST(Vector2, len)
{
   EXPECT_FLOAT_EQ(sqrt(4+9), Vector2d(2,3).length());
}

TEST(Vector2, dot)
{
   Vector2d a(0,1);
   Vector2d b(1,1);
   EXPECT_FLOAT_EQ(1, Vector2d::Dot(a,b));
   b = b.normalized();
   EXPECT_FLOAT_EQ(sqrt(1/2.0), Vector2d::Dot(a,b));
   a = Vector2d(1,0);
   b = Vector2d(0,1);
   EXPECT_FLOAT_EQ(0, Vector2d::Dot(a,b));

   a = Vector2d(1,0);
   b = Vector2d(1,0);
   EXPECT_FLOAT_EQ(1, Vector2d::Dot(a,b));

}

TEST(Vector3, add)
{
   Vector3d a(1, 2, 3);
   Vector3d b(4, 5, 6);
   a += b;
   EXPECT_EQ(a.x, 5);
   EXPECT_EQ(a.y, 7);
   EXPECT_EQ(a.z, 9);
}

TEST(Vector3, eq)
{
   Vector3d a(1, 2, 3);
   Vector3d b(1, 2, 3);
   EXPECT_EQ(a, b);
}

// Helen on 4/12/16
TEST(Math, getDif)
{
   Vector3d plane(4, 5, 6);
   Vector3d ownship(4, 5, 6);

   Vector3d result = getDifference(plane, ownship);
   Vector3d expected(0,0,0);

   EXPECT_EQ(expected.x, result.x);
   EXPECT_EQ(expected.y, result.y);
   EXPECT_EQ(expected.z, result.z);
}

TEST(Math, calcDist)
{
   float lat1 = 0.5;
   float lon1 = 0.5;

   float lat2 = 0.5;
   float lon2 = 0.5;

   EXPECT_EQ(0, calcDistance(lat1, lon1, lat2, lon2,0));
}

TEST(Math, bearing) {
   float bear = 180;

   EXPECT_FLOAT_EQ(-M_PI, bearingToRadians(bear));
}

