//
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <mlpack/methods/det/dtree.hpp>
#include "HiercClusteringCorrelation.h"
#include "SensorData.h"
#include "CorrelatedData.h"

/**
 * Implements single-linkage hierarchical clustering using euclidean minimum spanning tree (EMST)
 */
std::vector<CorrelatedData> HiercClusteringCorrelation::correlate(std::vector<SensorData> planes)
{
   std::vector<CorrelatedData> correlatedPlanes;
   std::vector<double> positions_x, positions_y, positions_z, velocities_x, velocities_y, velocities_z;
   int i, j, k, l, m, n, ndx, innerNdx;
   int size = planes.size(), originalSize;


   // euclidean distance = just between 2 points, dimention doesn't matter supposedly

   /*
    // general use of tree
    extern arma::mat data; // We want to find the MST of this dataset.
    DualTreeBoruvka<> dtb(data); // Create the tree with default options.
    // Find the MST.
    arma::mat mstResults;
    dtb.ComputeMST(mstResults);
    */


   // The number of clusters we are getting.
   size_t clusters = 2; //potentially empty clusters.
   // The assignments will be stored in this vector.
  // arma::Col<size_t> groupings;
   // The centroids will be stored in this matrix.
  // arma::mat centroids;
   // Initialize with the default arguments.
   //KMeans<> km;

   // Add individual sensor info (positions and velocities) into respective lists
   for (i = 0; i < size; i++)
   {
      positions_x.push_back(planes.at(i).getPurePosition().x);
   }
   for (j = 0; j < size; j++)
   {
      positions_y.push_back(planes.at(j).getPurePosition().y);
   }
   for (k = 0; k < size; k++)
   {
      positions_z.push_back(planes.at(k).getPurePosition().z);
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
   //Need to be column major
   std::vector<double> data;
   data.reserve(positions_x.size() + positions_y.size() + positions_z.size());
   for(int i = 0; i < size; i++)
   {
      data.push_back(positions_x[i]);
      data.push_back(positions_y[i]);
      data.push_back(positions_z[i]);
   }

   /*
   auto dataMtx = arma::Mat<double>(&data[0],3,planes.size());


   km.Cluster(dataMtx, clusters, groupings,centroids);

   //@TODO Correlated size should be different
   correlatedPlanes.reserve(clusters);
   for(int i = 0; i < clusters; i++)
   {
      correlatedPlanes.push_back(CorrelatedData(centroids.at(0,i),centroids.at(1,i),centroids.at(2,i),0,0,0));
   }
   for(int i = 0; i < size; i++)
   {
      correlatedPlanes[groupings.at(i)].addSensor(planes[i].getSensor(),planes[i].getPlaneTag());
   }



   }
*/
   return correlatedPlanes;
}