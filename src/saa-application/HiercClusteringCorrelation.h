//
// Created by Helen Hwang on 2/29/16.
//

#ifndef SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H
#define SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H

#include "SensorData.h"
#include "CorrelatedData.h"
#include "CorrelationStrategy.h"

class HiercClusteringCorrelation : public CorrelationStrategy
{
public:
   virtual std::vector<CorrelatedData> correlate(std::vector<SensorData> planes);
};
#endif //SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H
