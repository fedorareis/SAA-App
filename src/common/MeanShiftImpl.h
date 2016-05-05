//
// Created by Kyle Piddington on 4/26/16.
//

#ifndef SAA_APPLICATION_MEANSHIFTIMPL_H
#define SAA_APPLICATION_MEANSHIFTIMPL_H

#include "IMeanShift.h"


class MeanShiftImpl : public IMeanShift {
   public:
   MeanShiftImpl(double kBandwidth):
    kernel_bandwidth(kBandwidth)
   {   }

   virtual void Cluster(const arma::mat &mtx, arma::Col<size_t> &assignments, arma::mat &centroids);


   virtual void setWindow(double window) override;

   private:
    double kernel_bandwidth;

};


#endif //SAA_APPLICATION_MEANSHIFTIMPL_H
