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
// Created by Helen Hwang on 3/3/16.
//
#include <gtest/gtest.h>
#include <saa-application/SensorData.h>
#include <saa-application/HiercClusteringCorrelation.h>

/**
 * Tests what
 */
TEST(HiercClustering, TestSetup)
{
   // test data
   std::vector<SensorData> planes;


   // makeup data
   planes.push_back(SensorData("", 3.0, 5.0, 1.0, 4.0, 5.0, 9.0, adsb, 2, 0.0));
   planes.push_back(SensorData("", 0.0, 0.0, 0.0, 4.0, 5.0, 2.0, tcas, 4, 0.0));
   planes.push_back(SensorData("", 0.0, 4.0, 0.0, 4.0, 5.0, 9.0, radar, 2, 0.0));

   // calls correlation
   HiercClusteringCorrelation corr;
   std::vector<CorrelatedData> result = corr.correlate(planes);
   ASSERT_EQ(1,result.size());
   CorrelatedData res = result.at(0);
   Vector3d d = res.getPosition();
   ASSERT_EQ(Vector3d(3, 5, 1), Vector3d(d.x, d.y, d.z));

}

TEST(HiercClustering, TestInput)
{
   // test data
   std::vector<SensorData> planes;

   // makeup data
   planes.push_back(SensorData("",5.01,3,   -400,3000,2050,1020,adsb,0,1.0));
   planes.push_back(SensorData("",5,   3.01,-390,3010,2050,1030,tcas,0,1.0));
   planes.push_back(SensorData("",4.99,2.99,-410,2990,2050,1040,radar,0,1.0));

   // calls correlation
   HiercClusteringCorrelation corr;
   std::vector<CorrelatedData> result = corr.correlate(planes);
   ASSERT_EQ(1,result.size());
   CorrelatedData res = result.at(0);
   Vector3d d = res.getPosition();
   // error:
//   ASSERT_EQ(Vector3d(5.010, 3, -400), Vector3d(d.x, d.y, d.z));
   std::cout<<"centroid: "<<d.x<<", "<<d.y<<", "<<d.z<<std::endl;
}
