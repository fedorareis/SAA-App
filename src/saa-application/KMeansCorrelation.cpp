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
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <mlpack/methods/kmeans/kmeans.hpp>

#include "KMeansCorrelation.h"

#define NUM_AXES 3
#define MAX_ITERS 300

using namespace mlpack::kmeans;

std::vector<CorrelatedData> KMeansCorrelation::correlate(std::vector<SensorData> planes)
{
   std::vector<CorrelatedData> correlatedPlanes;
   int size = planes.size();
   std::cout << "Beginning KMeans" << std::endl;

   // The number of clusters we are getting. (Correlation Disabled)
   if (size == 0)
   {
      return correlatedPlanes;
   }

   // Potentially empty clusters.
   size_t clusters = size;
   // The assignments will be stored in this vector.
   arma::Row<size_t> groupings;
   // The centroids will be stored in this matrix.
   arma::mat centroids;
   // Initialize with the default arguments.
   KMeans<> km(MAX_ITERS);

   // Array to matrix conversion
   // Need to be column major
   std::vector<double> dataPoints;
   dataPoints.reserve(size * NUM_AXES);

   for (int i = 0; i < size; i++)
   {
      dataPoints.push_back(planes.at(i).getPurePosition().x);
      dataPoints.push_back(planes.at(i).getPurePosition().y);
      dataPoints.push_back(planes.at(i).getPurePosition().z);
   }

   auto dataMtx = arma::Mat<double>(&dataPoints[0], NUM_AXES, size);

   km.Cluster(dataMtx, clusters, groupings, centroids);

   //@TODO Correlated size should be different
   correlatedPlanes.reserve(clusters);

   for (int i = 0; i < clusters; i++)
   {
      correlatedPlanes.push_back(CorrelatedData(centroids.at(0, i), centroids.at(1, i), centroids.at(2, i), 0, 0, 0));
   }
   for (int i = 0; i < size; i++)
   {
      correlatedPlanes[groupings.at(i)].addSensor(planes[i].getSensor(), planes[i].getPlaneTag(), planes[i]
          .getTailNumber(), planes[i].getVelocity(), planes[i].getPurePosition());
   }

   std::cout << "Ending" << std::endl;

   return correlatedPlanes;
}
