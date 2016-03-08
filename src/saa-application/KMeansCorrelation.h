//
// Created by Kyle Reis on 11/17/15.
//

#ifndef SAA_APPLICATION_CORRELATION_H
#define SAA_APPLICATION_CORRELATION_H

#include "SensorData.h"
#include "CorrelatedData.h"
#include "CorrelationStrategy.h"

class KMeansCorrelation : public CorrelationStrategy
{
   public:
      void report();
      //void addPlane(/* When we have a plane class pass one in here*/);
      virtual std::vector<CorrelatedData> correlate(std::vector<SensorData> planes);
};
#endif //SAA_APPLICATION_CORRELATION_H
