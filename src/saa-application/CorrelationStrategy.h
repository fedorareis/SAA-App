//
// Created by Kyle Piddington on 2/25/16.
//

#ifndef SAA_APPLICATION_CORRELATIONSTRATEGY_H
#define SAA_APPLICATION_CORRELATIONSTRATEGY_H

#endif //SAA_APPLICATION_CORRELATIONSTRATEGY_H
/**
 * A correlation strategy can be used to correlate planes.
 * The strategy pattern is used to allow us to swap out
 * correlation algorithms.
 */
struct CorrelationStrategy
{
   virtual std::vector<CorrelatedData> correlate(std::vector<SensorData> planes) = 0;
};