//
// Created by lejonmcgowan on 2/3/16.
//

#include "NumPlanesVerificationTest.h"

#include "errors/NumPlanesTestCaseError.h"
bool NumPlanesVerificationTest::verify(TestCaseResult &result)
{
    bool correct = tc->getPlanes().size() == result.getPlanes().size();
    if (!correct)
    {
        error = std::make_shared<NumPlanesTestCaseError>(NumPlanesTestCaseError(-1));
    }

    return correct;
}
