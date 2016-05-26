//
// Created by Helen Hwang on 2/29/16.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include "HiercClusteringCorrelation.h"

/**
 * Internal tree structure
 */
struct node
{


};

/**
 * Calculates the EuclideanDistance
 */
int calculateEuclideanDistance(Vector3d aPoint, Vector3d bPoint)
{
   return sqrt((pow(bPoint.x - aPoint.x, 2))+ (pow(bPoint.y - aPoint.y, 2)) + (pow(bPoint.z - aPoint.z, 2)));
}

/*
 * Creates the tree of clusters
 */
std::vector<node> cluster(std::vector<SensorData> planes) {

}

/**
 * traverses mergedNdx and creates correlated planes
 */
std::vector<CorrelatedData> traverseMerged (std::vector<node> clustered) {
   std::vector<CorrelatedData> correlatedData;
   std::vector<bool> visited(clustered.size(), false);

   // find the right level

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



   // returns the list of correlated data
   return pointer;
}