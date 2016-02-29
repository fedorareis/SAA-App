//
// Created by Kyle Piddington on 2/4/16.
//

#ifndef SAA_APPLICATION_CORRECTSENSORVERIFICATIONTEST_H
#define SAA_APPLICATION_CORRECTSENSORVERIFICATIONTEST_H


#include "VerificationTest.h"

class CorrectSensorVerificationTest : public VerificationTest {

   public:
   CorrectSensorVerificationTest(const std::shared_ptr<TestCase> &tc) : VerificationTest(tc) { }

   virtual std::vector<std::shared_ptr<TestCaseError>> verify(TestCaseResult &result) ;

   virtual std::shared_ptr<TestCaseError> getError() ;

   private:
};


#endif //SAA_APPLICATION_CORRECTSENSORVERIFICATIONTEST_H
