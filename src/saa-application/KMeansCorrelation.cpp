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
      correlatedPlanes[groupings.at(i)].addSensor(planes[i].getSensor(), planes[i].getPlaneTag());
   }

   std::cout << "Ending" << std::endl;

   return correlatedPlanes;
}