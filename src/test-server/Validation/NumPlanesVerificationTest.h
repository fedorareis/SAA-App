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
   std::vector<std::shared_ptr<TestCaseError>> verify(TestCaseResult &result);

};

#endif //SAA_APPLICATION_NUMPLANESVERIFICATIONTEST_H
