/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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
   adsb=0,
   tcas,
   radar,
   ownship
};

class SensorData
{
public:
   SensorData(std::string tailNumber, float positionX, float positionY, float positionZ, float velocityX, float velocityY,
              float velocityZ, Sensor sensor, int planeId, double time) :
         tailNumber(tailNumber), sensor(sensor)
   {
      velocity = new Vector();
      position = new Vector();
      velocity->set_x(velocityX); // north
      velocity->set_y(velocityY); // east
      velocity->set_z(velocityZ); // down
      position->set_x(positionX); // north
      position->set_y(positionY); // east
      position->set_z(positionZ); // down
      planeTag = planeId;
      timeStamp = time;

   }

   void printPos();
   CDTIPlane* getCDTIPlane();

   Sensor getSensor()
   {
      return sensor;
   }

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

   std::string getTailNumber() {
        return tailNumber;
   }

   //Supersede Instance Variable (404)
   void supersedePosition(float newPositionX, float newPositionY, float newPositionZ)
   {
      position->set_x(newPositionX);
      position->set_y(newPositionY);
      position->set_z(newPositionZ);
   }

   void supersedeVelocity(float newVelocityX, float newVelocityY, float newVelocityZ)
   {
      velocity->set_x(newVelocityX);
      velocity->set_y(newVelocityY);
      velocity->set_z(newVelocityZ);
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