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

std::vector<std::shared_ptr<TestCaseError>> PositionVerificationTest::verify(TestCaseResult &result)
{
    //todo find reference to closest plane for error report
    bool correct = true;
    std::vector<std::shared_ptr<TestCaseError>> errors;

    for(int planeIndex = 0; planeIndex < tc->getPlanes().size() && correct; planeIndex++)
    {
        TestServerPlane testServerPlane = tc->getPlanes()[planeIndex];
        Vector3d* closestPosition = nullptr;
        bool match = false;

        //if there are planes to compare, set closest plane to first one for testing
        if(result.getPlanes().size() > 0)
        {
            closestPosition = new Vector3d(result.getPlanes()[0].getPosition());
        }

        for (int resultPlaneIndex = 0; resultPlaneIndex < result.getPlanes().size(); resultPlaneIndex++)
        {
            Vector3d resultPlanePos = result.getPlanes()[resultPlaneIndex].getPosition();

            Vector3d distance = getDifference(testServerPlane.getLatLongAlt(), tc->getOwnship().getLatLongAlt()) -
                  resultPlanePos;
            bool correctLat = fabs(distance.x) < THRESHOLD;
            bool correctLong = fabs(distance.y) < THRESHOLD;
            bool correctAlt = fabs(distance.z) < THRESHOLD;

            bool localMatch = correctLat && correctLong && correctAlt;
            match |= localMatch;

            //if plane is too far away to be a match, but is closest of the 'wrong' planes, report this as an error
            if(!localMatch && distance.getMagnitude() < closestPosition->getMagnitude())
            {
                closestPosition = new Vector3d(distance);
            }
        }

        PositionTestCaseError error = PositionTestCaseError(result.getTime(),testServerPlane.getLatLongAlt(),*closestPosition);
        error.setError(!match && closestPosition);
        errors.push_back(std::make_shared<PositionTestCaseError>(error));
    }

    return errors;
}
