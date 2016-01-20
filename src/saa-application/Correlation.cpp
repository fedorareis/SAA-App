//
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include <armadillo/include/armadillo.h>
#include <mlpack/src/mlpack/methods/kmeans/kmeans.hpp>

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

std::vector<Plane> Correlation::correlate(std::vector<Plane> planes)
{
   // FIGURING OUT HOW TO IMPORT Plane DATA INTO arma::mat

   // The dataset we are clustering.
   extern arma::mat data;
   // The number of clusters we are getting.
   extern size_t clusters;

   // The assignments will be stored in this vector.
   arma::Col<size_t> assignments;
   // The centroids will be stored in this matrix.
   arma::mat centroids;

   // Initialize with the default arguments.
   KMeans<> k;
   k.Cluster(data, clusters, assignments, centroids);

   // STILL FIGURING OUT THE THING -- vice versa tho

   return planes;
}