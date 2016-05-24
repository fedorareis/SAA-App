//
// Created by Kyle Piddington on 4/26/16.
//

#ifndef SAA_APPLICATION_MLPACKMEANSHIFTWRAPPER_H
#define SAA_APPLICATION_MLPACKMEANSHIFTWRAPPER_H
#include "IMeanShift.h"

class MLPackMeanshiftWrapper : public IMeanShift {
   public:
   virtual void setWindow(double window) override;

   void Cluster(const arma::mat & mtx,  arma::Col<size_t> assignments, arma::mat centroids);

};


#endif //SAA_APPLICATION_MLPACKMEANSHIFTWRAPPER_H
