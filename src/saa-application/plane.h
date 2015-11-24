//
// Created by Kyle Reis on 11/19/15.
//

#ifndef SAA_APPLICATION_PLANE_H
#define SAA_APPLICATION_PLANE_H

#include <string>
#include "common/protobuf/cdti.pb.h"

class Plane
{
public:
   Plane(std::string tailNumber, int positionX, int positionY, int positionZ, int velocityX, int velocityY,
            int velocityZ) : tailNumber(tailNumber)
   {
      velocity = new Vector();
      position = new Vector();
      velocity->set_x(velocityX);
      velocity->set_y(velocityY);
      velocity->set_z(velocityZ);
      position->set_x(positionX);
      position->set_y(positionY);
      position->set_z(positionZ);
   }

   CDTIPlane getCDTIPlane();

private:
   std::string tailNumber;
   Vector *velocity;
   Vector *position;
   CDTIPlane plane;
   CDTIPlane::Severity severity;
};

#endif //SAA_APPLICATION_PLANE_H
