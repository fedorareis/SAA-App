//
// Created by Kyle Piddington on 2/4/16.
//

#ifndef SAA_APPLICATION_CORRECTSENSORERROR_H
#define SAA_APPLICATION_CORRECTSENSORERROR_H


#include "TestCaseError.h"

class CorrectSensorError : public TestCaseError {

   public:
   CorrectSensorError(long timestamp);


   virtual std::string description() override;
};


#endif //SAA_APPLICATION_CORRECTSENSORERROR_H
