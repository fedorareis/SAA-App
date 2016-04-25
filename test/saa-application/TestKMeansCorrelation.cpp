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
