//
// Created by lejonmcgowan on 2/3/16.
//

#include "NumPlanesTestCaseError.h"

std::string NumPlanesTestCaseError::description()
{
 return "PLANE COUNT ERROR: expetected "
        + std::to_string(expected)
        + " planes but received "
        + std::to_string(actual)
        + " planes.";
}
