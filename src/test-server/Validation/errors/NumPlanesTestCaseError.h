//
// Created by lejonmcgowan on 2/3/16.
//

#ifndef SAA_APPLICATION_NUMPLANESTESTCASEERROR_H
#define SAA_APPLICATION_NUMPLANESTESTCASEERROR_H

#include "TestCaseError.h"

class NumPlanesTestCaseError : public TestCaseError
{
public:
    NumPlanesTestCaseError(long timestamp) : TestCaseError(timestamp)
    { }

    std::string description();
};

#endif //SAA_APPLICATION_NUMPLANESTESTCASEERROR_H
