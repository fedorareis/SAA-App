//
// Created by lejonmcgowan on 2/3/16.
//

#ifndef SAA_APPLICATION_POSITIONTESTCASEERROR_H
#define SAA_APPLICATION_POSITIONTESTCASEERROR_H

#include <common/Maths.h>
#include "TestCaseError.h"

class PositionTestCaseError : public TestCaseError
{
private:
    Vector3d expected, actual;
public:
    PositionTestCaseError(long timestamp, Vector3d expected, Vector3d actual) :
            TestCaseError(timestamp),
            expected(expected),
            actual(actual)
    { }
    std::string csvString() override;
    std::string description();
};

#endif //SAA_APPLICATION_POSITIONTESTCASEERROR_H
