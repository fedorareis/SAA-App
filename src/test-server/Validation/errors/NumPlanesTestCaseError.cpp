//
// Created by lejonmcgowan on 2/3/16.
//

#include "NumPlanesTestCaseError.h"

std::string NumPlanesTestCaseError::description()
{
 return "PLANE COUNT ERROR: expetected " + expected + " planes but received " + actual + " planes.";
}
