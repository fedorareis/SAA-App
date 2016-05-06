//
// Created by Kyle Piddington on 4/26/16.
//

#include <mlpack/methods/mean_shift/mean_shift.hpp>
#include "MLPackMeanshiftWrapper.h"
void Cluster(const arma::mat & mtx,  arma::Col<size_t> assignments, arma::mat centroids)
{
    mlpack::meanshift::MeanShift<true> meanShift;
    meanShift.Radius(0.01);
    meanShift.Cluster(mtx,assignments,centroids,false);

}

void MLPackMeanshiftWrapper::setWindow(double window) {
    //Do nothing for now.
}
