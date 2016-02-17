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
#include <common/Randomizer.h>
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
private:
    Randomizer *adsbNoise;
    Randomizer *tcasNoise;
    Randomizer *radarNoise;
public:
   SensorData(std::string tailNumber, float positionX, float positionY, float positionZ, float velocityX, float velocityY,
              float velocityZ, Sensor sensor, int planeId, double time) :
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
      planeTag = planeId;
      timeStamp = time;

      //add 3rd parameter is you want to put in a seed
      //todo: lookup ranges to put into this, possibly make up to 3 randomizers per sensor
      adsbNoise = new Randomizer(0, 0);
      tcasNoise = new Randomizer(0, 0);
      radarNoise = new Randomizer(0, 0);
   }

   void printPos();

   Sensor getSensor()
   {
      return sensor;
   }

   CDTIPlane* getCDTIPlane();

    Vector3d getPurePosition()
   {
      return Vector3d(position->x(),position->y(),position->z());
   }

   Vector3d  getVelocity()
   {
      return Vector3d(velocity->x(),velocity->y(),velocity->z());
   }

   int getPlaneTag()
   {
      return planeTag;
   }

   double getTimeStamp()
   {
      return timeStamp;
   }


private:
   Sensor sensor;
   std::string tailNumber;
   Vector *velocity;
   Vector *position;
   CDTIPlane *plane = new CDTIPlane();
   CDTIPlane::Severity severity;
   int planeTag;
   double timeStamp;
};

#endif //SAA_APPLICATION_SENSORDATA_H