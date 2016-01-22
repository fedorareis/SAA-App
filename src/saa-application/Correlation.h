//
// Created by Kyle Reis on 11/17/15.
//

#ifndef SAA_APPLICATION_CORRELATION_H
#define SAA_APPLICATION_CORRELATION_H

#include "SensorData.h"

class Correlation
{
   public:
      void report();
      //void addPlane(/* When we have a plane class pass one in here*/);
      virtual std::vector<Plane> correlate(std::vector<Plane> planes);
};
#endif //SAA_APPLICATION_CORRELATION_H
