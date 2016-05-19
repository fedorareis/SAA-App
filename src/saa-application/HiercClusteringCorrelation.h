//
// Created by Helen Hwang on 2/29/16.
//

#ifndef SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H
#define SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H

#include "SensorData.h"
#include "CorrelatedData.h"
#include "CorrelationStrategy.h"
#include "ClusteringTechnique.h"

class HiercClusteringCorrelation : public CorrelationStrategy
{
public:
   //void addPlane(/* When we have a plane class pass one in here*/);
   virtual std::vector<CorrelatedData> correlate(std::vector<SensorData> planes);

private:
   ClusteringTechnique& cluster;
};
#endif //SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H
