//
// Created by Kyle Piddington on 2/29/16.
//

#include <mlpack/core.hpp>
#include <mlpack/methods/mean_shift/mean_shift.hpp>
#include "MeanShiftCorrelation.h"

std::vector<CorrelatedData> MeanShiftCorrelation::correlate(std::vector<SensorData> planes) {
   std::vector<CorrelatedData> correlatedPlanes;
   std::vector<double> data;
   bool correlationFailed = false;
   if(planes.size() == 0)
   {
      return correlatedPlanes;
   }
   //Otherwise try and cluster
   for(int i = 0 ; i < planes.size(); i++){
      SensorData plane = planes[i];
      if(this->currFlags & COR_POS)
      {
         data.push_back(plane.getPurePosition().x);
         data.push_back(plane.getPurePosition().y);
         data.push_back(plane.getPurePosition().z / FEET_TO_NAUT_MILES);
      }
      if(this->currFlags & COR_VEL)
      {
         data.push_back(plane.getVelocity().x / FEET_TO_NAUT_MILES);
         data.push_back(plane.getVelocity().y / FEET_TO_NAUT_MILES);
         data.push_back(plane.getVelocity().z / FEET_TO_NAUT_MILES);
      }
   }
   //Data is constructed, set dimensionality.
   int dimensionality = 0;

   if(this->currFlags & COR_POS)
   {
      dimensionality += 3;
   }
   if(this->currFlags & COR_VEL)
   {
      dimensionality += 3;
   }

   arma::Col<size_t> assignments;
   arma::mat centroids;
   meanshift->setWindow(10);
   auto dataMtx = arma::Mat<double>(&data[0],dimensionality,planes.size());
   //dataMtx = dataMtx.; //Transpose data matrix
   //Radius test
   //try
   //{
   meanshift->Cluster(dataMtx, assignments, centroids);

  // }
   /*
    * MeanShift has trouble processing data sets. For now, we'll return a blank correlation..
    */


   /**
    * If correlation fails, use the assignments from the previous run and vector summations to create new planes.
    */
   if(correlationFailed && prevAssignments.size() > 0)
   {
      correlatedPlanes.resize(planes.size());
      /* Sum correlations */
      for(int i = 0; i < planes.size(); i++)
      {
         correlatedPlanes[prevAssignments.at(i)].addVelocity(planes[i].getVelocity());
         correlatedPlanes[prevAssignments.at(i)].addPosition(planes[i].getPurePosition());
         correlatedPlanes[prevAssignments.at(i)].addSensor(planes[i].getSensor(),planes[i].getPlaneTag());
      }
      /*Trim planes that didn't actually correlate*/
      correlatedPlanes.erase(std::remove_if(correlatedPlanes.begin(), correlatedPlanes.end(),
                                            [](CorrelatedData & data){return data.getSensor().size() == 0;}),
                     correlatedPlanes.end());
      //For the remainder of planes, average
      for(auto cPlane : correlatedPlanes)
      {
         Vector3d velocity = cPlane.getVelocity();
         Vector3d position = cPlane.getPosition();
         position.x /= cPlane.getSensor().size();
         position.y /= cPlane.getSensor().size();
         position.z /= cPlane.getSensor().size();
         cPlane.setPosition(position);
      }
      return correlatedPlanes;
   }
   else if(correlationFailed)
   {
      return correlatedPlanes;
   }
   else
   {


      correlatedPlanes.reserve(centroids.n_cols);
      for (int i = 0; i < centroids.n_cols; i++) {
         correlatedPlanes.push_back(CorrelatedData(centroids.at(0, i), centroids.at(1, i), centroids.at(2, i), 0, 0, 0));
      }
      for (int i = 0; i < planes.size(); i++) {
         correlatedPlanes[assignments.at(i)].addVelocity(planes[i].getVelocity());
         correlatedPlanes[assignments.at(i)].addSensor(planes[i].getSensor(), planes[i].getPlaneTag());


      }
      prevAssignments = assignments;
   }
   return correlatedPlanes;



}

MeanShiftCorrelation::MeanShiftCorrelation(double wSize, int flags) {
   this->cWindow = wSize;
   this->currFlags = flags;
   meanshift = std::make_shared<MeanShiftImpl>(0.2);

}
