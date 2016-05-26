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
