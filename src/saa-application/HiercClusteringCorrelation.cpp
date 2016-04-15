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
 * Clusters data till there's only 1 cluster or no longer able to cluster
 */
std::vector<int> cluster(std::vector<SensorData> planes, arma::Mat<double> planesMtx) {
   // keeps the merged planes
   std::vector<int> mergedNdx(planes.size(), -1);

   // default option, might have to add bool for native
   // unsure if this is smart pointer or not
   mlpack::emst::DualTreeBoruvka<> dtb(planesMtx);
   arma::mat distanceMtx;

   // computes the distance planesMtx
   dtb.ComputeMST(distanceMtx);

   // prints the planesMtx
   std::cout << distanceMtx.t() << std::endl;

   //TODO: combine all the printing thing, sensor checking, and numMerge checking
   std::cout << "hc-distanceMtx.at(0) is " << distanceMtx.at(0) << std::endl;
   SensorData plane1 = planes[(int) distanceMtx.at(0)];
   std::cout<<"hc-plane at row 0 col 0 has "<<plane1.getPurePosition().x;
   std::cout<<" "<<plane1.getPurePosition().y<<" "<< plane1.getPurePosition().z<<std::endl;
   std::cout << "hc-distanceMtx.at(1) is " << distanceMtx.at(1) << std::endl;
   SensorData plane2 = planes[(int) distanceMtx.at(1)];
   std::cout<<"hc-plane at row 0 col 1 has ";
   std::cout<<"hc-plane at row 0 col 0 has "<<plane2.getPurePosition().x;
   std::cout<<" "<<plane2.getPurePosition().y<<" "<< plane2.getPurePosition().z<<std::endl;


   // sensor can't be same!
   if(plane1.getSensor()!= plane2.getSensor())
   {
      std::cout<<"sensor not same; able to merge!"<<std::endl;
      std::cout<<"merged data is ";
      Vector3d merged = mergeTwoVectors(plane1.getPurePosition(), plane2.getPurePosition());
      std::cout<<merged.x<<" "<<merged.y<<" "<<merged.z<<std::endl;
   }

   // and can't be more than 3 sensors in 1 cluster

   // how distance matrix is organized
   int lessNdx = distanceMtx.at(0);
   int grtrNdx = distanceMtx.at(1);

   // merge closest together into cluster
  // if(lessThanThreeSensors(mergedNdx, lessNdx)) {
   // update index -> If count == 3, DON'T MERGE and merge the next closest together
   if(lessThanThreeSensors(mergedNdx, lessNdx))
   {
      // updates the ndx
      while(mergedNdx[lessNdx] != -1)
      {
         lessNdx = mergedNdx[lessNdx];
      }
      mergedNdx[lessNdx] = grtrNdx;
   }
   else
   {
      std::cout<<"can't merge these; merge the next closest together"<<std::endl;
   }


   // TODO: merge == basically addition and division
   SensorData merged = SensorData("", 0, 4, 0, 0, 0, 0, adsb, 1, 0);
      // create new SensorData by merging both values

   planes.erase(planes.begin()+1); // erases the index 1
   planes.erase(planes.begin()+2); // erases the index "3"
   planes.push_back(merged); // adds the new merged planes

   std::cout<<"new plane list has "<<planes.size()<<" items"<<std::endl;
   planesMtx = initializeMtx(planes);

   // deletes the tree
   // Question? calling deconstructor vs using delete? Or are those same? Or are they even necessary?
   dtb.~DualTreeBoruvka();

   mlpack::emst::DualTreeBoruvka<> dt(planesMtx);

   // computes the distance planesMtx
   dt.ComputeMST(distanceMtx);

   // prints the planesMtx
   std::cout << distanceMtx.t() << std::endl;

   //TODO: implement the following
      // update planes matrix by calling planesMtx = initialize() with new planes vector

      // calculate distance matrix
      // merge till there's only 1 cluster or no longer able to cluster = no change in distanceMtx
      // 1 cluster = col element == 1
  // } else {
      // merge the next available closest together
  // }

   return mergedNdx;
}

/**
 * traverses mergedNdx and creates correlated planes
 */
std::vector<CorrelatedData> traverseMerged (std::vector<int> mergedNdx, std::vector<SensorData> planes) {
   std::vector<CorrelatedData> correlatedData;
   // -1 means it's not merged with any
   // else, follow the index and mark as done
   // calculate "centroid": sum/num for all -> use mergeTwoVectors
   std::vector<bool> visited(planes.size(), false);

   //TODO: implement the following
   // for each index, while not visited, traverse and merge
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

