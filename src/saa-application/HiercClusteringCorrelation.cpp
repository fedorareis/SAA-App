//
// Created by Helen Hwang on 2/29/16.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <mlpack/core.hpp>
#include <mlpack/methods/emst/dtb.hpp>
#include "HiercClusteringCorrelation.h"


/**
 * Implements single-linkage hierarchical clustering using euclidean minimum spanning tree (EMST)
 */
std::vector<CorrelatedData> HiercClusteringCorrelation::correlate(std::vector<SensorData> planes)
{
   std::vector<CorrelatedData> correlatedPlanes;
   int size = planes.size();

   std::vector<double> data;
   if(planes.size() == 0)
   {
      return correlatedPlanes;
   }

   // put data into matrix for clustering algorithm to use
   for(int i = 0 ; i < planes.size(); i++){
      SensorData plane = planes[i];

      // only getting position for now
      data.push_back(plane.getPurePosition().x);
      data.push_back(plane.getPurePosition().y);
      data.push_back(plane.getPurePosition().z);
   }

   auto dataMtx = arma::Mat<double>(&data[0],3,size);

   // default option, might have to add bool for native
   mlpack::emst::DualTreeBoruvka<> dtb(dataMtx);
   arma::mat mstResults;

   dtb.ComputeMST(mstResults);

   //TODO: NOT IMPLEMENTED YET

   // prints the matrix
   std::cout<<"hc-result matrix contains "<< mstResults.n_rows<<" row elements"<<std::endl;
   std::cout<<"hc-result matrix contains "<< mstResults.n_cols<<" col elements"<<std::endl;
   std::cout<<"<index    >index      distance"<<std::endl;
   std::cout<<mstResults.t()<<std::endl;
   // indices refers back to the vector that was used to created
   // and the matrix is ordered by the minimum distance
   /* A single-linkage clustering can be obtained from the EMST by deleting all edges longer than a given cluster length. */
   std::cout<<"hc-result matrix has max "<< mstResults.max()<<" and min "<< mstResults.min()<<std::endl;
   std::cout<<"hc-result matrix index 0 has connection to: " <<std::endl;

   /* Helen's observation
    *
    * Few useful functions
    * Printing .t() prints the values in table format
    * .n_rows actually gives the number of columns which is 3 all the time
    * .n_cols gives the number of rows, which I think is size-1?
    * min() returns the minimum distance, max() returns the maximum distance
    * So calling this computeMST() returns the "iteration"
    *
    * so the matrix is ordered by the minimum distance
    * First column is the lesser of the index, second column is the greater index, and the third column is the distance
    *

   // This is the "steps" for single linked hierarchical clustering
   // This is computed by calling computeMST()
   Step 1. Construct the distance matrix from the given pattern matrix

    // there's a cor(x, y) function in arma
    // as long as it's in same dimension, arma can correlate vector or matrix.
   Step 2. Assign each pattern to a cluster

    // I think you can merge by calling cor(x, y) with vector returns the correlated vector
    // that contains the dot product
   Step 3. Determine the smallest entry in the distance matrix D, say D(c1, c2) and merge the
            two clusters c1 and c2

   Step 4. Update the distance matrix D, by deleting the row and column corresponding to
             the cluster c2, and rename row c1 and column c1 to (c1, c2).
            Assign the min[D(c3, c1), D(c3, c2)] to D(c3, (c1, c2)) and D((c1, c2), c3) for all c3’s

   Step 5. If only one cluster is left, stop. Else, go to Step 3

    * */

   return correlatedPlanes;
}

