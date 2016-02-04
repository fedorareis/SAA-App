//
// Created by lejonmcgowan on 2/2/16.
//

#include <test-server/planes/TestServerPlane.h>
#include "PositionVerificationTest.h"

bool PositionVerificationTest::verify(TestCaseResult &result)
{
    bool correct = true;
    for(int planeIndex = 0; planeIndex < tc->getPlanes().size && correct; planeIndex++)
    {
        correct = correct && (tc->getPlanes()[planeIndex].position == result.getPlanes()[planeIndex].getPosition());
    }

    return correct;
}
