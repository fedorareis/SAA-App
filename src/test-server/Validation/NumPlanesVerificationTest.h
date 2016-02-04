//
// Created by lejonmcgowan on 2/3/16.
//

#ifndef SAA_APPLICATION_NUMPLANESVERIFICATIONTEST_H
#define SAA_APPLICATION_NUMPLANESVERIFICATIONTEST_H

#include "VerificationTest.h"

class NumPlanesVerificationTest: public VerificationTest
{

public:
    NumPlanesVerificationTest(const std::shared_ptr<TestCase> &tc) : VerificationTest(tc)
    { }

    bool verify(TestCaseResult& result);
};

#endif //SAA_APPLICATION_NUMPLANESVERIFICATIONTEST_H
