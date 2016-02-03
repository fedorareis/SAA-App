//
// Created by lejonmcgowan on 1/26/16.
//

#ifndef SAA_APPLICATION_MOCKVERIFICATIONTEST_H
#define SAA_APPLICATION_MOCKVERIFICATIONTEST_H

#include <test-server/TestCase.h>
#include "test-server/Validation/VerificationTest.h"
#include <gmock/gmock.h>

class VerificationTest_test : public VerificationTest
{
private:
    TestCase& testCase;
public:
    VerificationTest_test(TestCase& testCase): testCase(testCase){};
    MOCK_METHOD1(verify,bool (TestCaseResult&) );
};

#endif //SAA_APPLICATION_MOCKVERIFICATIONTEST_H
