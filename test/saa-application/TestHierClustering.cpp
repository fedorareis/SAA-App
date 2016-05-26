//
// Created by Helen Hwang on 3/3/16.
//
#include <gtest/gtest.h>
#include <mlpack/methods/emst/dtb.hpp>
#include <saa-application/SensorData.h>
#include <saa-application/HiercClusteringCorrelation.h>

/**
 * Tests what
 */
TEST(HiercClustering, TestSetup)
{
   std::vector<double> data;

   // test data
   std::vector<SensorData> planes;
   /*
   SensorData(std::string tailNumber, float positionX, float positionY, float positionZ, float velocityX, float velocityY,
         float velocityZ, Sensor sensor, int planeId, double time) :
   tailNumber(tailNumber), sensor(sensor)
   */

   // makeup data
   planes.push_back(SensorData("", 0.0, 9.0, 0.0, 4.0, 10.0, 9.0, tcas, 0, 0.0));
   planes.push_back(SensorData("", 3.0, 5.0, 1.0, 4.0, 5.0, 9.0, adsb, 2, 0.0));
   planes.push_back(SensorData("", 0.0, 0.0, 0.0, 4.0, 5.0, 2.0, tcas, 4, 0.0));
   planes.push_back(SensorData("", 0.0, 4.0, 0.0, 4.0, 5.0, 9.0, radar, 2, 0.0));
   planes.push_back(SensorData("", 4.0, 0.0, 9.0, 7.0, 2.0, 4.0, adsb, 5, 0.0));

   std::cout<<"ht-planes have "<<planes.size()<<" planes"<<std::endl;

   // calls correlation
   HiercClusteringCorrelation corr;
   // std::vector<CorrelatedData> result = corr.correlate(planes);
   // prints the tree of cluster

//   ASSERT_EQ(0,result.size());

}
