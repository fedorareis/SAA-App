//
// Created by Kyle Piddington on 2/23/16.
//
#include <gtest/gtest.h>
#include <mlpack/methods/mean_shift/mean_shift.hpp>

#include <mlpack/methods/kmeans/kmeans.hpp>

TEST(GaussModeling,TestSetup)
{
   /**
    * Try Gaussian model with one gassuian
    */
   mlpack::meanshift::MeanShift<> meanShift;
   arma::Col<size_t> assignments;
   arma::mat centroids;
   std::vector<double> data;
   for(int i = 0; i < 12; i++) {
      double x = (5 + (double) rand() / INT_MAX * 0.5 - 0.25) * (i % 2 ? -1 : 1);
      double y = (5 + (double) rand() / INT_MAX * 0.5 - 0.25) * (i % 2 ? -1 : 1);
      data.push_back(x);
      data.push_back(y);
   }
   auto dataMtx = arma::Mat<double>(&data[0],2,data.size()/2);
   meanShift.Cluster(dataMtx, assignments, centroids);
   /*
    * Clusters should alternate
    */
   for(int i = 0; i < data.size()/2; i+=2)
   {
      EXPECT_NE(assignments(i),assignments(i+1));
      std::cout << assignments(i) <<  " , " << assignments(i+1) << std::endl;
   }




}

