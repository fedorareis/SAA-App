//
// Created by Kyle Piddington on 4/26/16.
//
//Logic credit to https://github.com/mattnedrich/MeanShift_cpp/blob/master/MeanShift.cpp, a minimal
// implementation of mean-shift.
#include "MeanShiftImpl.h"

#define EPSILON 0.0000001

double euclidean_distance(const arma::vec vec_a, const arma::vec vec_b){
    arma::vec diff = vec_b - vec_a;
    return arma::norm(diff,diff.n_cols);

}

double gaussian_kernel(double distance, double kernel_bandwidth){
    double temp =  exp(-(distance*distance) / (kernel_bandwidth));
    return temp;
}


/**
 * Shift the point towards the centroid of all surrounding points.
 * Points is treated as a density field (modeled using the gaussian kernel).
 */
arma::vec shift_point(const arma::vec &point, const arma::mat &points, double kernel_bandwidth) {
    arma::vec shifted_point(point.size());
    shifted_point.zeros();

    double total_weight = 0;
    //For every point in the initial distribution:
    for(int i=0; i< points.n_cols; i++){
        arma::vec temp_point = points.col(i);
        //Get the distance to the point at tmp_point.
        double distance = euclidean_distance(point, temp_point);
        //Get the influence of the point (based off of the distance)
        double weight = gaussian_kernel(distance, kernel_bandwidth);
        //Shift towards the point
        shifted_point += temp_point*weight;
        total_weight += weight;
    }
    shifted_point/=total_weight;
    return shifted_point;
}


void MeanShiftImpl::Cluster(const arma::mat &mtx, arma::Col<size_t> &assignments, arma::mat &centroids) {
    std::vector<bool> stop_moving(mtx.n_cols,false);
    assignments.resize(mtx.n_cols);

    arma::mat shifted_points = mtx;
    double max_shift_distance;
    do {
        max_shift_distance = 0;
        arma::mat tmp = shifted_points;
        for(int i=0; i<shifted_points.n_cols; i++){
            if (!stop_moving[i]) {
                arma::vec point_new = shift_point(shifted_points.col(i), mtx, kernel_bandwidth);
                double shift_distance = euclidean_distance(point_new, shifted_points.col(i));
                if(shift_distance > max_shift_distance){
                    max_shift_distance = shift_distance;
                }
                if(shift_distance <= EPSILON) {
                    stop_moving[i] = true;
                }
                shifted_points.col(i) = point_new;
            }
        }
        std::cout << "max shift dist: " << max_shift_distance << std::endl;
    } while (max_shift_distance > EPSILON);

    //Calculate cluster assignments
    for(int iter = 0; iter < assignments.size(); iter++)
    {
        assignments[iter] = -1;
    }
    //Loop through each points, and find points within euclidian_dist that have
    //not been clustered.
    int cCluster = 0;
    std::vector<arma::vec> centroidVec;
    for(int iter = 0; iter < assignments.size(); iter++)
    {
        if(assignments[iter] != -1)
        {
            continue;
        }
        else
        {
            assignments[iter] = cCluster;
            arma::vec cur = shifted_points.col(iter);
            centroidVec.push_back(cur);
            for(int rest = iter + 1; rest < assignments.size(); rest++) {
                arma::vec next = shifted_points.col(rest);
                double dist = euclidean_distance(cur,next);
                if(dist <= EPSILON)
                {
                    assignments[rest] = cCluster;
                }
            }
            cCluster++;
        }
    }
    centroids.resize(mtx.n_rows,centroidVec.size());
    for(int i = 0; i < centroidVec.size(); i++)
    {
        centroids.col(i) = centroidVec[i];
    }


    //Build clusters/assignments (kdtree-nearest neighbors?)




    //Yeah, that thing
}



void MeanShiftImpl::setWindow(double window) {
    kernel_bandwidth = window;
}
