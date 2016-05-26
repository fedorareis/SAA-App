//
// Created by Kyle Piddington on 1/26/16.
//

#include "TcasSensor.h"
#include <math.h>
#include <test-server/TestServer.h>

TcasReport TcasSensor::createReport(const TestServerPlane &plane,
                                    const TestServerPlane &ownship) {

   //Create range from position
   float range = calcDistance(plane.getLatitude(),plane.getLongitude(),ownship.getLatitude(),ownship.getLongitude(), ownship.getAltitude());
   float positionX = calcDistance(plane.getLatitude(), ownship.getLongitude(), ownship.getLatitude(),
                                  ownship.getLongitude(), ownship.getAltitude()) * (plane.getLatitude() < ownship.getLatitude()? -1 : 1);
   float positionY = calcDistance(ownship.getLatitude(), plane.getLongitude(), ownship.getLatitude(),
                                  ownship.getLongitude(), ownship.getAltitude()) * (plane.getLongitude() < ownship.getLongitude()? -1 : 1);

   float positionZ = (float) (-1.0*(plane.getAltitude()-ownship.getAltitude()));

   Vector2d difference = Vector2d(positionX,positionY).normalized();
   Vector2d leftVec = Vector2d(-ownship.getEastVelocity(),ownship.getNorthVelocity()).normalized();
   float angle = (float)acos((float)Vector2d::Dot(Vector2d(ownship.getNorthVelocity(),ownship.getEastVelocity()).normalized(),
                                        difference));
   bool negBearing = Vector2d::Dot(leftVec,difference) <= 0;
   //Angle offset
   //if 'difference' is to the left, use negabive bearings.
   float bearing = 180.f/M_PI * atan2(leftVec.y, leftVec.x);//180.f/M_PI * angle * (negBearing ? -1 : 1);
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




