//
// Created by lejonmcgowan on 2/3/16.
//

#include "NumPlanesVerificationTest.h"

bool NumPlanesVerificationTest::verify(TestCaseResult &result)
{
    return tc->getPlanes().size() == result.getPlanes().size();
}
