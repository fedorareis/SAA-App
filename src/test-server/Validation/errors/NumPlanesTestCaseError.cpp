//
// Created by lejonmcgowan on 2/3/16.
//

#include "NumPlanesTestCaseError.h"

std::string NumPlanesTestCaseError::description()
{
 return "PLANE COUNT ERROR: expected "
        + std::to_string(expected)
        + " planes but received "
        + std::to_string(actual)
        + " planes.";
}

std::string NumPlanesTestCaseError::csvString() {
 return std::to_string(getTimestamp()) + ",numPlanes"
        + "," + std::to_string(expected) + "," + std::to_string(actual) + "\n";
}