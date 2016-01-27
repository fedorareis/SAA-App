//
// Created by lejonmcgowan on 1/26/16.
//

#ifndef SAA_APPLICATION_VERIFICATIONTEST_H
#define SAA_APPLICATION_VERIFICATIONTEST_H

#include "TestCaseResult.h"

class VerificationTest
{
public:
    virtual bool verify(TestCaseResult& result) = 0;
};

#endif //SAA_APPLICATION_VERIFICATIONTEST_H
