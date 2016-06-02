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
// Created by Kyle Piddington on 2/23/16.
//
#include <gtest/gtest.h>
#include <mlpack/methods/mean_shift/mean_shift.hpp>

#include <mlpack/methods/kmeans/kmeans.hpp>
#include "common/IMeanShift.h"
#include "common/MeanShiftImpl.h"
TEST(GaussModeling,TestSetup)
{
   /**
    * Try Gaussian model with one gassuian
    */
   mlpack::meanshift::MeanShift<> meanShift;
   arma::Col<size_t> assignments;
   arma::mat centroids;
   std::vector<double> data;
   for(int i = 0; i < 20; i++) {
      double x = (5 + (double) rand() / INT_MAX * 0.5 - 0.25) * (i % 2 ? -1 : 1);
      double y = (5 + (double) rand() / INT_MAX * 0.5 - 0.25) * (i % 2 ? -1 : 1);
      data.push_back(x);
      data.push_back(y);
   }
   auto dataMtx = arma::Mat<double>(&data[0],2,data.size()/2);
   meanShift.Cluster(dataMtx, assignments, centroids,false);
   /*
    * Clusters should alternate
    */
   for(int i = 0; i < data.size()/2; i+=2)
   {
      EXPECT_NE(assignments(i),assignments(i+1));
      std::cout << assignments(i) <<  " , " << assignments(i+1) << std::endl;
   }


}

TEST(MyShittyCode,DoesItWork)
{

   IMeanShift * shift = new MeanShiftImpl(1.5);
   arma::Col<size_t> assignments;
   arma::mat centroids;
   std::vector<double> data;
   for(int i = 0; i < 20; i++) {
      double x = (5 + (double) rand() / INT_MAX * 0.5 - 0.25) * (i % 2 ? -1 : 1);
      double y = (5 + (double) rand() / INT_MAX * 0.5 - 0.25) * (i % 2 ? -1 : 1);
      data.push_back(x);
      data.push_back(y);
   }
   auto dataMtx = arma::Mat<double>(&data[0],2,data.size()/2);
   shift->Cluster(dataMtx, assignments, centroids);
   /*
    * Clusters should alternate
    */
   for(int i = 0; i < data.size()/2; i+=2)
   {
      EXPECT_NE(assignments(i),assignments(i+1));
      std::cout << assignments(i) <<  " , " << assignments(i+1) << std::endl;
   }
   delete shift;
}

