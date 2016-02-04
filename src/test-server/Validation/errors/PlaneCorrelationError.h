//
// Created by Kyle Piddington on 1/19/16.
//

#ifndef SAA_APPLICATION_PLANECORRELATIONERROR_H
#define SAA_APPLICATION_PLANECORRELATIONERROR_H

#include "test-server/Validation/errors/TestCaseError.h"
class PlaneCorrelationError : public TestCaseError {

   public:
   PlaneCorrelationError(int exp, int gotten, long time);

   virtual std::string description() override;

   private:
   std::string desc;
};


#endif //SAA_APPLICATION_PLANECORRELATIONERROR_H
