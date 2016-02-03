//
// Created by lejonmcgowan on 1/26/16.
//

#ifndef SAA_APPLICATION_VERIFICATIONTEST_H
#define SAA_APPLICATION_VERIFICATIONTEST_H

#include "TestCaseResult.h"

class VerificationTest
{
public:
    VerificationTest(std::shared_ptr<TestCase> tc);
    virtual bool verify(TestCaseResult& result) = 0;

   protected:
      const std::shared_ptr<TestCase> tc;

};

#endif //SAA_APPLICATION_VERIFICATIONTEST_H
