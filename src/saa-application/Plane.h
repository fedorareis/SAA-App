/*
 * Created by Kyle Reis on 11/19/15.
 *
 * X, Y, and Z, refer to North, East, and Down respectively
 * relative to the Ownship.
*/

#ifndef SAA_APPLICATION_PLANE_H
#define SAA_APPLICATION_PLANE_H

#include <string>
#include <common/Maths.h>
#include "common/protobuf/cdti.pb.h"

enum Sensor
{
   adsb,
   tcas,
   radar
};

class Plane
{
public:
   Plane(std::string tailNumber, float positionX, float positionY, float positionZ, float velocityX, float velocityY,
         float velocityZ) :
         tailNumber(tailNumber)
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

   void printPos();

   CDTIPlane* getCDTIPlane();
   Vector3d  getPosition()
   {
      return Vector3d(position->x(),position->y(),position->z());
   }
private:
   Sensor sensor;
   std::string tailNumber;
   Vector *velocity;
   Vector *position;
   CDTIPlane *plane = new CDTIPlane();
   CDTIPlane::Severity severity;
};

#endif //SAA_APPLICATION_PLANE_H