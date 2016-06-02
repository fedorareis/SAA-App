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
// Created by Kyle Reis on 11/17/15.
//

#ifndef SAA_APPLICATION_CORRELATION_H
#define SAA_APPLICATION_CORRELATION_H

#include "SensorData.h"
#include "CorrelatedData.h"
#include "CorrelationStrategy.h"

class KMeansCorrelation : public CorrelationStrategy
{
   public:
    /**
      * First algorithm implemented for correlation.
      *
      * Calculates and correlates the raw sensor data to be sent and analyzed
      * in the Decision-Making module.
      *
      * @param planes The raw sensor data sent from the test server once per second.
      * @return The correlated sensor data being sent to Decision module.
      */
      virtual std::vector<CorrelatedData> correlate(std::vector<SensorData> planes);
};
#endif //SAA_APPLICATION_CORRELATION_H
