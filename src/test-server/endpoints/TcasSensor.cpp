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
//
// Created by Kyle Piddington on 1/26/16.
//

#include "TcasSensor.h"
#include <math.h>
#include <test-server/TestServer.h>

TcasReport TcasSensor::createReport(const TestServerPlane &plane,
                                    const TestServerPlane &ownship) {

   //Create range from position
   Vector3d pos(plane.getLatitude(), plane.getLongitude(), plane.getAltitude());
//   float range = calcDistance(pos.x, pos.y,ownship.getLatitude(),ownship.getLongitude(), ownship.getAltitude());
   float positionX = calcDistance(pos.x, ownship.getLongitude(), ownship.getLatitude(),
                                  ownship.getLongitude(), ownship.getAltitude()) * (pos.x < ownship
       .getLatitude()? -1 : 1);
   float positionY = calcDistance(ownship.getLatitude(), pos.y, ownship.getLatitude(),
                                  ownship.getLongitude(), ownship.getAltitude()) * (pos.y < ownship
       .getLongitude()? -1 : 1);

   float range = std::sqrt(positionX * positionX + positionY * positionY);
   float positionZ = (float) (-1.0*(plane.getAltitude()-ownship.getAltitude()));

//   Vector2d difference = Vector2d(positionX,positionY).normalized();
//   Vector2d leftVec = Vector2d(ownship.getEastVelocity(),ownship.getNorthVelocity()).normalized();
//   float angle = (float)acos((float)Vector2d::Dot(Vector2d(ownship.getNorthVelocity(),ownship.getEastVelocity()).normalized(),
//                                        difference));
//   bool negBearing = Vector2d::Dot(leftVec,difference) <= 0;
   //Angle offset
   //if 'difference' is to the left, use negabive bearings.
   float bearing = radToDeg(atan2(positionY, positionX));//180.f/M_PI * angle * (negBearing ? -1 : 1);
   if (bearing < 0) {
      bearing += 360;
   }

   //tuple of the position to send to report. is in format (range,bearing,altitude)
   Vector3d finalPosition(range, bearing, positionZ);
   //std::cout << range << std::endl;
   //std::cout << bearing << std::endl;
   if (jitter)
   {
      finalPosition = TestServer::scrambleTCAS(finalPosition);
   }

   TcasReport report;
   report.set_bearing((float) finalPosition.y);
   report.set_altitude((float) finalPosition.z);

   report.set_range(finalPosition.x);
           /* (float) sqrt(finalPosition.x * finalPosition.x + finalPosition.z * finalPosition.z / (FEET_TO_NAUT_MILES *
                                                                                                 FEET_TO_NAUT_MILES))
                                                                                                 );*/
   report.set_id(plane.getTcasId());
   report.set_plane_id(plane.getId());

   return report;
}

void TcasSensor::sendData(const TestServerPlane &plane, const TestServerPlane & ownship) {
   this->getEndpoint().getSocket() << TcasSensor::createReport(plane, ownship);
}

TcasSensor::TcasSensor(SensorEndpoint *endpoint, bool jitter) :
        Sensor(endpoint, jitter)
{

}




