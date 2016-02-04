//
// Created by lejonmcgowan on 2/2/16.
//

#ifndef SAA_APPLICATION_POSITIONVERIFICATIONTEST_H
#define SAA_APPLICATION_POSITIONVERIFICATIONTEST_H

#include "VerificationTest.h"

class PositionVerificationTest: public VerificationTest
{

public:
    PositionVerificationTest(const std::shared_ptr<TestCase> &tc) : VerificationTest(tc)
    { }

    bool verify(TestCaseResult& result);
};

#endif //SAA_APPLICATION_POSITIONVERIFICATIONTEST_H
