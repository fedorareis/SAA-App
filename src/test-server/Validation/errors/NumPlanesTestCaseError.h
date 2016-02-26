//
// Created by lejonmcgowan on 2/3/16.
//

#ifndef SAA_APPLICATION_NUMPLANESTESTCASEERROR_H
#define SAA_APPLICATION_NUMPLANESTESTCASEERROR_H

#include "TestCaseError.h"

class NumPlanesTestCaseError : public TestCaseError
{
private:
    int actual,expected;
public:
    NumPlanesTestCaseError(long timestamp,int numPLanesExpeted, int numPlanesActual) :
            TestCaseError(timestamp),
            actual(numPlanesActual),
            expected(numPLanesExpeted)
    { }

    std::string description();
};

#endif //SAA_APPLICATION_NUMPLANESTESTCASEERROR_H
