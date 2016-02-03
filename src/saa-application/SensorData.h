/*
 * Created by Kyle Reis on 11/19/15.
 *
 * X, Y, and Z, refer to North, East, and Down respectively
 * relative to the Ownship.
*/

#ifndef SAA_APPLICATION_SENSORDATA_H
#define SAA_APPLICATION_SENSORDATA_H

#include <string>
#include <common/Maths.h>
#include "common/protobuf/cdti.pb.h"

enum Sensor
{
   adsb,
   tcas,
   radar,
   ownship
};

class SensorData
{
public:
   SensorData(std::string tailNumber, float positionX, float positionY, float positionZ, float velocityX, float velocityY,
              float velocityZ, Sensor sensor) :
         tailNumber(tailNumber), sensor(sensor)
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

   Sensor getSensor()
   {
      return sensor;
   }

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

#endif //SAA_APPLICATION_SENSORDATA_H