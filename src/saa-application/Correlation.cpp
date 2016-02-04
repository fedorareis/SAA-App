//
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <armadillo>
#include <math.h>

#include "Correlation.h"
#include "common/protobuf/adsb.pb.h"
#include "common/protobuf/ownship.pb.h"
#include "common/protobuf/radar.pb.h"
#include "common/protobuf/tcas.pb.h"

using namespace mlpack::kmeans;

void Correlation::report()
{
   std::cout << "We are correlating some stuff" << std::endl;
}

std::vector<CorrelatedData> Correlation::correlate(std::vector<SensorData> planes)
{
   std::vector<CorrelatedData> correlatedPlanes;
   std::vector<double> positions_x, positions_y, positions_z, velocities_x, velocities_y, velocities_z;
   int i, j, k, l, m, n, ndx, innerNdx;
   int size = planes.size(), originalSize;

   // The dataset(s) we are clustering.
   arma::mat pos_x_data, pos_y_data, pos_z_data, vel_x_data, vel_y_data, vel_z_data;
   // The number of clusters we are getting.
   size_t clusters = size;
   // The assignments will be stored in this vector.
   arma::Col<size_t> pos_x_assign, pos_y_assign, pos_z_assign, vel_x_assign, vel_y_assign, vel_z_assign;
   // The centroids will be stored in this matrix.
   arma::mat pos_x_cen, pos_y_cen, pos_z_cen, vel_x_cen, vel_y_cen, vel_z_cen;
   // Initialize with the default arguments.
   KMeans<> km;

   // Add individual sensor info (positions and velocities) into respective lists
   for (i = 0; i < size; i++)
   {
      positions_x.push_back(planes.at(i).getPosition().x);
   }
   for (j = 0; j < size; j++)
   {
      positions_y.push_back(planes.at(j).getPosition().y);
   }
   for (k = 0; k < size; k++)
   {
      positions_z.push_back(planes.at(k).getPosition().z);
   }
   for (l = 0; l < size; l++)
   {
      velocities_x.push_back(planes.at(l).getVelocity().x);
   }
   for (m = 0; m < size; m++)
   {
      velocities_y.push_back(planes.at(m).getVelocity().y);
   }
   for (n = 0; n < size; n++)
   {
      velocities_z.push_back(planes.at(n).getVelocity().z);
   }

   // Array to matrix conversion
   pos_x_data = arma::mat(positions_x);
   pos_y_data = arma::mat(positions_y);
   pos_z_data = arma::mat(positions_z);
   vel_x_data = arma::mat(velocities_x);
   vel_y_data = arma::mat(velocities_y);
   vel_z_data = arma::mat(velocities_z);

   km.Cluster(pos_x_data, clusters, pos_x_assign, pos_x_cen);
   km.Cluster(pos_y_data, clusters, pos_y_assign, pos_y_cen);
   km.Cluster(pos_z_data, clusters, pos_z_assign, pos_z_cen);
   km.Cluster(vel_x_data, clusters, vel_x_assign, vel_x_cen);
   km.Cluster(vel_y_data, clusters, vel_y_assign, vel_y_cen);
   km.Cluster(vel_z_data, clusters, vel_z_assign, vel_z_cen);

   // Creating list of CorrelatedData
   for(ndx = 0; ndx < size; ndx++)
   {
      originalSize = correlatedPlanes.size();

      for(innerNdx = 0; innerNdx < originalSize; innerNdx++)
      {
         CorrelatedData data = correlatedPlanes.at(innerNdx);

         if ((fabs(data.getPosition().x - pos_x_assign) < 0.01) &&
               (fabs(data.getPosition().y - pos_y_assign) < 0.01) &&
               (fabs(data.getPosition().z - pos_z_assign) < 0.01) &&
               (fabs(data.getVelocity().x - vel_x_assign) < 0.01) &&
               (fabs(data.getVelocity().y - vel_y_assign) < 0.01) &&
               (fabs(data.getVelocity().z - vel_z_assign) < 0.01))
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

   return correlatedPlanes;
}