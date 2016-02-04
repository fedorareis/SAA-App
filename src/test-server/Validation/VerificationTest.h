//
// Created by lejonmcgowan on 1/26/16.
//

#ifndef SAA_APPLICATION_VERIFICATIONTEST_H
#define SAA_APPLICATION_VERIFICATIONTEST_H

#include "TestCaseResult.h"
#include "../TestCase.h"
#include "test-server/Validation/errors/TestCaseError.h"

class VerificationTest
{
public:
    VerificationTest(std::shared_ptr<TestCase> tc): tc(tc){}
    virtual bool verify(TestCaseResult& result) = 0;

    TestCaseError &getError()
    { return *error; }

   protected:
      const std::shared_ptr<TestCase> tc;
    std::shared_ptr<TestCaseError> error;

};

#endif //SAA_APPLICATION_VERIFICATIONTEST_H
