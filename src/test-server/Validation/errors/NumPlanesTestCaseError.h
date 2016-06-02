/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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

    NumPlanesTestCaseError(const NumPlanesTestCaseError & other):
        TestCaseError(other),
        actual(other.actual),
        expected(other.expected){}

    std::string description();
   std::string csvString();
};

#endif //SAA_APPLICATION_NUMPLANESTESTCASEERROR_H
