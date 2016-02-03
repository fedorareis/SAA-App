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

   std::vector<double> positions_x;
   std::vector<double> positions_y;
   std::vector<double> positions_z;

   // FIGURING OUT HOW TO IMPORT Plane DATA INTO arma::mat
   for (int i = 0; i < planes.size(); i++)
   {
      positions_x.push_back(planes.at(i).getPosition().x);
   }
   for (int j = 0; j < planes.size(); j++)
   {
      positions_x.push_back(planes.at(j).getPosition().y);
   }
   for (int k = 0; k < planes.size(); k++)
   {
      positions_x.push_back(planes.at(k).getPosition().z);
   }

   // The dataset we are clustering.
   arma::mat data;
   // The number of clusters we are getting.
   size_t clusters = planes.size();

   // The assignments will be stored in this vector.
   arma::Col<size_t> assignments;
   // The centroids will be stored in this matrix.
   arma::mat centroids;

   // Initialize with the default arguments.
   KMeans<> k;
   k.Cluster(data, clusters, assignments, centroids);

   // STILL FIGURING OUT THE THING -- vice versa tho

   return correlatedPlanes;
}