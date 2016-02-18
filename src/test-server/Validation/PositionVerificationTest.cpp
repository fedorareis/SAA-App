//
// Created by lejonmcgowan on 2/2/16.
//

#include <test-server/planes/TestServerPlane.h>
#include "PositionVerificationTest.h"

#include "errors/PositionTestCaseError.h"

//todo move this into the testcase properly
#define THRESHOLD 0.1f

//todo: move this to maths.h
bool equalsThreshold(float num1, float num2, float threshold)
{
    return fabs(num1 - num2) < threshold;
}

bool PositionVerificationTest::verify(TestCaseResult &result)
{
    //todo find reference to closest plane for error report
    bool correct = true;
    for(int planeIndex = 0; planeIndex < tc->getPlanes().size() && correct; planeIndex++)
    {
        TestServerPlane testServerPlane = tc->getPlanes()[planeIndex];
        bool match = false;
        for (int resultPlaneIndex = 0; resultPlaneIndex < result.getPlanes().size(); resultPlaneIndex++)
        {

            Vector3d resultPlanePos = result.getPlanes()[resultPlaneIndex].getPosition();
            Vector3d distance =
                  getDifference(testServerPlane.getLatLongAlt(), tc->getOwnship().getLatLongAlt()) -
                  resultPlanePos;
            bool correctLat = fabs(distance.x) < THRESHOLD;
            bool correctLong = fabs(distance.y) < THRESHOLD;
            bool correctAlt = fabs(distance.z) < THRESHOLD;

            match |= correctLat && correctLong && correctAlt;
        }

        correct &= match;
    }

    if (!correct)
    {
        error = std::make_shared<PositionTestCaseError>(PositionTestCaseError(-1));
    }
    return correct;
}
