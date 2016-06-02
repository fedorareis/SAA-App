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
// Created by Helen Hwang on 2/29/16.
//

#ifndef SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H
#define SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H

#define NOT_USED  0 /* node is currently not used */
#define LEAF_NODE 1 /* node contains a leaf node */
#define A_MERGER  2 /* node contains a merged pair of root clusters */
#define MAX_LABEL_LEN 16
#define alloc_mem(N, T) (T *) calloc(N, sizeof(T))
#define alloc_fail(M) fprintf(stderr,                                   \
                              "Failed to allocate memory for %s.\n", M)
#define invalid_node(I) fprintf(stderr,                                 \
                                "Invalid cluster node at index %d.\n", I)
#include "SensorData.h"
#include "CorrelatedData.h"
#include "CorrelationStrategy.h"

class HiercClusteringCorrelation : public CorrelationStrategy
{
public:
   virtual std::vector<CorrelatedData> correlate(std::vector<SensorData> planes);
};
#endif //SAA_APPLICATION_HIERCCLUSTERINGCORRELATION_H
