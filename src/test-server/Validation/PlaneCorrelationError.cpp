//
// Created by Kyle Piddington on 1/19/16.
//

#include <string>
#include "PlaneCorrelationError.h"

PlaneCorrelationError::PlaneCorrelationError(int exp, int gotten, long timeStamp):
   TestCaseError(timeStamp)
{
   desc = std::string("Correlation error, got " + std::to_string(gotten) + " plane, Expected " +
                            std::to_string(exp) + " planes");

}

std::string PlaneCorrelationError::description() {
   return desc;
}
