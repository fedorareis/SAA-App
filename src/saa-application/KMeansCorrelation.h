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
    /**
      * First algorithm implemented for correlation.
      *
      * Calculates and correlates the raw sensor data to be sent and analyzed
      * in the Decision-Making module.
      *
      * @param planes The raw sensor data sent from the test server once per second.
      * @return The correlated sensor data being sent to Decision module.
      */
      virtual std::vector<CorrelatedData> correlate(std::vector<SensorData> planes);
};
#endif //SAA_APPLICATION_CORRELATION_H
