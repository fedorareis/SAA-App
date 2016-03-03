//
// Created by Hae Ri Hwang on 3/3/16.
//
#include <gtest/gtest.h>
#include <mlpack/methods/emst/dtb.hpp>
#include <saa-application/SensorData.h>

TEST(HiercClustering, TestSetup)
{
   std::vector<double> data;

   // test data
   std::vector<SensorData> planes;

   //TODO: makeup test data and put them into planes

   // put data into vector for matrix initialization
   for(int i = 0 ; i < planes.size(); i++){
      SensorData plane = planes[i];

      // only getting position for now
      data.push_back(plane.getPurePosition().x);
      data.push_back(plane.getPurePosition().y);
      data.push_back(plane.getPurePosition().z);
   }

   // generate matrix
   auto dataMtx = arma::Mat<double>(&data[0],3,planes.size());

   // generate emst
   mlpack::emst::DualTreeBoruvka<> dtb(dataMtx);

   // result matrix
   arma::mat mstResults;

   dtb.ComputeMST(mstResults);

   // print data from each row
   for(arma::uword row = 0; row < mstResults.n_elem; row++) {
      std::cout<<"x: "<<mstResults.at(row, 0)<<" y: "<<mstResults.at(row, 1)<<" z: "<<mstResults.at(row, 2)<<std::endl;
   }

};
