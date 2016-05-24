//
// Created by lejonmcgowan on 2/3/16.
//

#include "PositionTestCaseError.h"

std::string PositionTestCaseError::description()
{
  return "POSITION ERROR: expected position of " + expected.toString() + " but closest plane was" + actual.toString();
}

std::string PositionTestCaseError::csvString() {
  return std::to_string(getTimestamp()) + ",Position"
         + "," + std::to_string(expected.x) + "," + std::to_string(actual.x)
         + "," + std::to_string(expected.y) + "," + std::to_string(actual.y)
         + "," + std::to_string(expected.z) + "," + std::to_string(actual.z) + "\n";
}
