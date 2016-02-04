//
// Created by lejonmcgowan on 2/2/16.
//

#include <test-server/planes/TestServerPlane.h>
#include "PositionVerificationTest.h"

bool PositionVerificationTest::verify(TestCaseResult &result)
{
    bool correct = true;
    for(int planeIndex = 0; planeIndex < tc->getPlanes().size() && correct; planeIndex++)
    {
        TestServerPlane testServerPlane = tc->getPlanes()[planeIndex];
        Vector3d resultPlanePos = result.getPlanes()[planeIndex].getPosition();

        bool correctLat = resultPlanePos.x == testServerPlane.getLatitude();
        bool correctLong = resultPlanePos.y == testServerPlane.getLongitude();
        bool correctAlt = resultPlanePos.z == testServerPlane.getAltitude();

        correct &= (correctLat && correctLong && correctAlt);
    }

    return correct;
}
