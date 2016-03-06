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
   // traverse the mstResults for stuff...LOL

   return correlatedPlanes;
}