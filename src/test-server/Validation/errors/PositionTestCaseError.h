//
// Created by lejonmcgowan on 2/3/16.
//

#ifndef SAA_APPLICATION_POSITIONTESTCASEERROR_H
#define SAA_APPLICATION_POSITIONTESTCASEERROR_H

#include "TestCaseError.h"

class PositionTestCaseError : public TestCaseError
{
public:
    PositionTestCaseError(long timestamp) : TestCaseError(timestamp)
    { }

    std::string description();
};

#endif //SAA_APPLICATION_POSITIONTESTCASEERROR_H
