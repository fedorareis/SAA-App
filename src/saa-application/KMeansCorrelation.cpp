//
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <mlpack/methods/kmeans/kmeans.hpp>

#include "KMeansCorrelation.h"

using namespace mlpack::kmeans;

void KMeansCorrelation::report()
{
   std::cout << "We are correlating some stuff" << std::endl;
}

std::vector<CorrelatedData> KMeansCorrelation::correlate(std::vector<SensorData> planes) {
   std::vector<CorrelatedData> correlatedPlanes;
   std::vector<double> positions_x, positions_y, positions_z, velocities_x, velocities_y, velocities_z;
   int i, j, k, l, m, n, ndx, innerNdx;
   int size = planes.size(), originalSize;
   std::cout << "Beginning KMeans" << std::endl;

   // The number of clusters we are getting. (Correlation Disabled)
   if(planes.size() == 0)
   {
      return correlatedPlanes;
   }

   size_t clusters = planes.size(); //potentially empty clusters.
   // The assignments will be stored in this vector.
   arma::Row<size_t> groupings;
   // The centroids will be stored in this matrix.
   arma::mat centroids;
   // Initialize with the default arguments.
   KMeans<> km(300);

   // Add individual sensor info (positions and velocities) into respective lists
   for (i = 0; i < size; i++) {
      positions_x.push_back(planes.at(i).getPurePosition().x);
   }
   for (j = 0; j < size; j++) {
      positions_y.push_back(planes.at(j).getPurePosition().y);
   }
   for (k = 0; k < size; k++) {
      positions_z.push_back(planes.at(k).getPurePosition().z);
   }
   for (l = 0; l < size; l++) {
      velocities_x.push_back(planes.at(l).getVelocity().x);
   }
   for (m = 0; m < size; m++) {
      velocities_y.push_back(planes.at(m).getVelocity().y);
   }
   for (n = 0; n < size; n++) {
      velocities_z.push_back(planes.at(n).getVelocity().z);
   }

   // Array to matrix conversion
   //Need to be column major
   std::vector<double> data;
   data.reserve(positions_x.size() + positions_y.size() + positions_z.size());
   for (int i = 0; i < size; i++) {
      data.push_back(positions_x[i]);
      data.push_back(positions_y[i]);
      data.push_back(positions_z[i]);
   }

   auto dataMtx = arma::Mat<double>(&data[0], 3, planes.size());


   km.Cluster(dataMtx, clusters, groupings,centroids);
   /*
      km.Cluster(pos_y_data, clusters, pos_y_assign, pos_y_cen);
      km.Cluster(pos_z_data, clusters, pos_z_assign, pos_z_cen);
      km.Cluster(vel_x_data, clusters, vel_x_assign, vel_x_cen);
      km.Cluster(vel_y_data, clusters, vel_y_assign, vel_y_cen);
      km.Cluster(vel_z_data, clusters, vel_z_assign, vel_z_cen);
    */

   //@TODO Correlated size should be different
   correlatedPlanes.reserve(clusters);
   for (int i = 0; i < clusters; i++) {
      correlatedPlanes.push_back(CorrelatedData(centroids.at(0, i), centroids.at(1, i), centroids.at(2, i), 0, 0, 0));
   }
   for (int i = 0; i < size; i++) {
      correlatedPlanes[groupings.at(i)].addSensor(planes[i].getSensor(), planes[i].getPlaneTag());
   }


   // Creating list of CorrelatedData
   /*
   for(ndx = 0; ndx < size; ndx++)
   {
      originalSize = correlatedPlanes.size();

      for(innerNdx = 0; innerNdx < originalSize; innerNdx++)
      {
         CorrelatedData data = correlatedPlanes.at(innerNdx);

         if ((fabs(data.getPosition().x - pos_x_assign(ndx)) < 0.01) &&
             (fabs(data.getPosition().y - pos_y_assign(ndx)) < 0.01) &&
             (fabs(data.getPurePosition().z - pos_z_assign(ndx)) < 0.01) &&
             (fabs(data.getVelocity().x - vel_x_assign(ndx)) < 0.01) &&
             (fabs(data.getVelocity().y - vel_y_assign(ndx)) < 0.01) &&
             (fabs(data.getVelocity().z - vel_z_assign(ndx)) < 0.01))
         {
            break;
         }
            // If assignment does not exist, create new CorrelatedData
         else
         {
            correlatedPlanes.push_back(CorrelatedData(pos_x_assign(ndx), pos_y_assign(ndx), pos_z_assign(ndx), vel_x_assign(ndx), vel_y_assign(ndx), vel_z_assign(ndx)));
         }
      }
      // First iteration
      if(originalSize == 0)
      {
         correlatedPlanes.push_back(CorrelatedData(pos_x_assign(ndx), pos_y_assign(ndx), pos_z_assign(ndx), vel_x_assign(ndx), vel_y_assign(ndx), vel_z_assign(ndx)));
      }
         // Size won't change if assignment exists in vector<CorrelatedData>
      else if(originalSize == correlatedPlanes.size())
      {
         // If sensor does not exist, add sensor flag
         std::vector<Sensor> sensors = correlatedPlanes.at(innerNdx).getSensor();
         Sensor sensor = planes.at(ndx).getSensor();

         if ( std::find( sensors.begin(), sensors.end(), sensor ) != sensors.end())
         {
            correlatedPlanes.at(ndx).addSensor(sensor, planes.at(ndx).getPlaneTag());
         }
      }
   }
   */
   std::cout << "Ending" << std::endl;
   return correlatedPlanes;
}
