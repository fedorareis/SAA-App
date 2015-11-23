//
// Created by Kyle Reis on 11/19/15.
//

#ifndef SAA_APPLICATION_PLANE_H
#define SAA_APPLICATION_PLANE_H

#include <string>

class Plane
{
public:
   std::string getTailNumber();
   int getRelativeBearing();
   int getRelativeElevation();
   std::string getMessage();
private:
   std::string tailNumber;
   int relativeBearing;
   int relativeElevation;
   std::string message;
};

#endif //SAA_APPLICATION_PLANE_H
