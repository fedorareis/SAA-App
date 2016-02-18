//
// Created by lejonmcgowan on 1/26/16.
//

#ifndef SAA_APPLICATION_VERIFICATIONTEST_H
#define SAA_APPLICATION_VERIFICATIONTEST_H

#include "TestCaseResult.h"
#include "../TestCase.h"
#include "test-server/Validation/errors/TestCaseError.h"
#include <vector>

class VerificationTest
{
public:
    VerificationTest(std::shared_ptr<TestCase> tc): tc(tc){}
    virtual std::vector<std::shared_ptr<TestCaseError>> verify(TestCaseResult& result) = 0;

   protected:
      const std::shared_ptr<TestCase> tc;

};

#endif //SAA_APPLICATION_VERIFICATIONTEST_H
