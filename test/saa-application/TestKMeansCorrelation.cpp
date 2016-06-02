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
// Created by Leah Pichay on 3/11/2016.
//
#include <gtest/gtest.h>
#include <saa-application/SensorData.h>
#include <saa-application/KMeansCorrelation.h>

TEST(KMeansCorrelation,TestSetup)
{
   // Test plane data
   std::vector<SensorData> planes;

   // Create mock data
   planes.push_back(SensorData("", 4.0, 0.0, 9.0, 7.0, 2.0, 4.0, adsb, 5, 0.0));
   planes.push_back(SensorData("", 0.0, 9.0, 0.0, 4.0, 10.0, 9.0, tcas, 0, 0.0));
   planes.push_back(SensorData("", 0.0, 4.0, 0.0, 4.0, 5.0, 9.0, adsb, 3, 0.0));
   planes.push_back(SensorData("", 0.0, 0.0, 0.0, 4.0, 5.0, 2.0, adsb, 4, 0.0));
   planes.push_back(SensorData("", 0.0, 9.0, 0.0, 4.0, 10.0, 9.0, tcas, 1, 0.0));
   planes.push_back(SensorData("", 0.0, 4.0, 0.0, 4.0, 5.0, 9.0, adsb, 2, 0.0));

   std::cout << "There are " << planes.size() << " plane inputs." << std::endl;

   // Call correlation
   KMeansCorrelation corr;
   std::vector<CorrelatedData> result = corr.correlate(planes);

   ASSERT_EQ(0, 1);
}
