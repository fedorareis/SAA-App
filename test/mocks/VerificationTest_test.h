//
// Created by lejonmcgowan on 1/26/16.
//

#ifndef SAA_APPLICATION_MOCKVERIFICATIONTEST_H
#define SAA_APPLICATION_MOCKVERIFICATIONTEST_H

#include "test-server/TestCase.h"
#include "test-server/Validation/VerificationTest.h"
#include <gmock/gmock.h>

class VerificationTest_test : public VerificationTest
{
private:
public:
    VerificationTest_test(std::shared_ptr<TestCase> testCase):
            VerificationTest(testCase)
    {
    };
    bool verify(TestCaseResult& result){return true;}
};

#endif //SAA_APPLICATION_MOCKVERIFICATIONTEST_H