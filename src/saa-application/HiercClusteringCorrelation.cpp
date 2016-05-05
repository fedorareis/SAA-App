//
// Created by Helen Hwang on 2/29/16.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <mlpack/core.hpp>
#include <mlpack/methods/emst/dtb.hpp>
#include "HiercClusteringCorrelation.h"

/**
 * Initializes and returns matrix with positions data
 */
arma::Mat<double> initializeMtx(std::vector<SensorData> planes)
{
   std::vector<double> data;

   // put data into matrix for clustering algorithm to use
   for(int i = 0 ; i < planes.size(); i++){
      SensorData plane = planes[i];

      // only getting position for now
      data.push_back(plane.getPurePosition().x);
      data.push_back(plane.getPurePosition().y);
      data.push_back(plane.getPurePosition().z);
   }

   // initializes the matrix
   return arma::Mat<double>(&data[0], 3, planes.size());
}

/**
 * Traverses the mergedNdx to check there's no more than 3 sensors in cluster
 */
bool lessThanThreeSensors(std::vector<int> mergedNdx, int ndx) {
   int counter = 0;
   std::cout<<"in lessThanThreeSensors with ndx "<<ndx<<std::endl;

   // traverses the ndx
   while(mergedNdx[ndx] != -1) {
      std::cout<<ndx<<" is merged with ";

      ndx = mergedNdx[ndx];
      counter++;

      std::cout<<ndx<<" and count is now at "<<counter<<std::endl;
   }

   std::cout<<"new ndx is "<<ndx<<" and count is "<<counter<<std::endl;
   // if there's less than 3 sensor, you can still cluster
   return counter < 3 ? true : false;
}

/**
 * Merges 2 vectors and returns the result
 */
Vector3d mergeTwoVectors(Vector3d v1, Vector3d v2) {
   return Vector3d((int)((v1.x + v2.x)/2), (int)((v1.y + v2.y)/2), (int)((v1.z + v2.z)/2));
}

/*
 * Clusters data till there's only 1 cluster and then parse the tree
 */
std::vector<int> cluster(std::vector<SensorData> planes, arma::Mat<double> planesMtx) {
   // keeps the merged planes
   std::vector<int> mergedNdx(planes.size(), -1);

   mlpack::emst::DualTreeBoruvka<> dtb(planesMtx);
   arma::mat distanceMtx;

   // computes the distance planesMtx
   dtb.ComputeMST(distanceMtx);

   std::cout << distanceMtx.t() << std::endl;

   // just merge the closest together

   return mergedNdx;
}

/**
 * traverses mergedNdx and creates correlated planes
 */
std::vector<CorrelatedData> traverseMerged (std::vector<int> mergedNdx, std::vector<SensorData> planes) {
   std::vector<CorrelatedData> correlatedData;
   std::vector<bool> visited(planes.size(), false);

   //TODO: implement the following
   /*
      follow the cluster, check whether there's
    */

   /* correlatedPlanes.reserve(centroids.n_cols);
   for (int i = 0; i < centroids.n_cols; i++) {
      correlatedPlanes.push_back(CorrelatedData(centroids.at(0, i), centroids.at(1, i), centroids.at(2, i), 0, 0, 0));
   }
   for (int i = 0; i < planes.size(); i++) {
      correlatedPlanes[assignments.at(i)].addSensor(planes[i].getSensor(), planes[i].getPlaneTag());
   } */

   return correlatedData;
}

/**
 * Implements single-linkage hierarchical clustering using euclidean minimum spanning tree (EMST)
 */
std::vector<CorrelatedData> HiercClusteringCorrelation::correlate(std::vector<SensorData> planes)
{
   std::vector<CorrelatedData> pointer;
   // checks whether there are planes or not
   if(planes.size() == 0)
   {
      return pointer;
   }

   // initializes the matrix
   auto toCorrelateMtx = initializeMtx(planes);

   // returns the hierarchical clustered "tree"
   std::vector<int> clustered = cluster(planes, toCorrelateMtx);

   // returns the list of correlated data
   return traverseMerged(clustered, planes);
}