//
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <armadillo>

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

std::vector<CDTIPlane> Correlation::correlate(std::vector<SensorData> planes)
{
   std::vector<CDTIPlane> correlatedPlanes;
   std::vector<double> positions_x, positions_y, positions_z, velocities_x, velocities_y, velocities_z;
   int i, j, k, l, m, n;

   // The dataset(s) we are clustering.
   arma::mat pos_x_data, pos_y_data, pos_z_data, vel_x_data, vel_y_data, vel_z_data;
   // The number of clusters we are getting.
   size_t clusters = planes.size();
   // The assignments will be stored in this vector.
   arma::Col<size_t> pos_x_assign, pos_y_assign, pos_z_assign, vel_x_assign, vel_y_assign, vel_z_assign;
   // The centroids will be stored in this matrix.
   arma::mat pos_x_cen, pos_y_cen, pos_z_cen, vel_x_cen, vel_y_cen, vel_z_cen;
   // Initialize with the default arguments.
   KMeans<> k;

   // Add individual sensor info (positions and velocities) into respective lists
   for (i = 0; i < planes.size(); i++)
      positions_x.push_back(planes.at(i).getPosition().x);
   for (j = 0; j < planes.size(); j++)
      positions_y.push_back(planes.at(j).getPosition().y);
   for (k = 0; k < planes.size(); k++)
      positions_z.push_back(planes.at(k).getPosition().z);
   for (l = 0; l < planes.size(); l++)
      velocities_x.push_back(planes.at(l).getVelocity().x);
   for (m = 0; m < planes.size(); m++)
      velocities_y.push_back(planes.at(m).getVelocity().y);
   for (n = 0; n < planes.size(); n++)
      velocities_z.push_back(planes.at(n).getVelocity().z);

   // Array to matrix conversion
   pos_x_data = arma::mat(positions_x);
   pos_y_data = arma::mat(positions_y);
   pos_z_data = arma::mat(positions_z);
   vel_x_data = arma::mat(velocities_x);
   vel_y_data = arma::mat(velocities_y);
   vel_z_data = arma::mat(velocities_z);

   k.Cluster(pos_x_data, clusters, pos_x_assign, pos_x_cen);
   k.Cluster(pos_y_data, clusters, pos_y_assign, pos_y_cen);
   k.Cluster(pos_z_data, clusters, pos_z_assign, pos_z_cen);
   k.Cluster(vel_x_data, clusters, vel_x_assign, vel_x_cen);
   k.Cluster(vel_y_data, clusters, vel_y_assign, vel_y_cen);
   k.Cluster(vel_z_data, clusters, vel_z_assign, vel_z_cen);

   // STILL FIGURING OUT THE THING -- vice versa tho

   // Convert either assignments or centroids into vectors

   // If centroid exists in vector<CDTIPlane>
   //    If sensor does not exist
   //       Add sensor flag
   // If centroid does not exist
   //    Create new CDTIPlane

   return correlatedPlanes;
}