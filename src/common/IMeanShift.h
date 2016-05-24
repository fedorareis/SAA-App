//
// Created by Kyle Piddington on 4/26/16.
//

#ifndef SAA_APPLICATION_IMEANSHIFT_H
#define SAA_APPLICATION_IMEANSHIFT_H

#include <armadillo>

class IMeanShift {
   public:
    virtual void Cluster(const arma::mat & mtx,  arma::Col<size_t> & assignments, arma::mat & centroids) = 0;
    virtual void setWindow(double window) = 0;

};


#endif //SAA_APPLICATION_IMEANSHIFT_H
