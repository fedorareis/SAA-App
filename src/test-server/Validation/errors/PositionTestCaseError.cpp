//
// Created by lejonmcgowan on 2/3/16.
//

#include "PositionTestCaseError.h"

std::string PositionTestCaseError::description()
{
  return "POSITION ERROR: expected position of " + expected.toString() + " but closest plane was" + actual.toString();
}
