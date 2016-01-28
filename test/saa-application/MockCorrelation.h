//
// Created by Hae Ri Hwang on 1/20/16.
//

#ifndef SAA_APPLICATION_MOCKCORRELATION_H
#define SAA_APPLICATION_MOCKCORRELATION_H
#include <googletest/googlemock/include/gmock/gmock.h>
#include <googletest/googlemock/include/gmock/gmock-generated-function-mockers.h>
#include <googletest/googletest/include/gtest/internal/gtest-internal.h>
#include <googletest/googletest/include/gtest/internal/gtest-port.h>
#include <googletest/googlemock/include/gmock/internal/gmock-generated-internal-utils.h>
#include "saa-application/Correlation.h"

class MockCorrelation :: Correlation
{
   public:
      MOCK_METHOD1(correlate, std::vector<Plane>(std::vector<Plane>));
};

#endif //SAA_APPLICATION_MOCKCORRELATION_H
