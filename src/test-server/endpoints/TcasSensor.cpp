//
// Created by Kyle Piddington on 1/26/16.
//

#include "TcasSensor.h"
#include "common/Maths.h"
#include <iostream>
TcasReport TcasSensor::createReport(const TestServerPlane &plane,
                                    const TestServerPlane &ownship) {

   //Create range from position
   float range = calcDistance(plane.getLatitude(),plane.getLongitude(),ownship.getLatitude(),ownship.getLongitude());
   float positionX = calcDistance(plane.getLatitude(), ownship.getLatitude(), ownship.getLatitude(),
                                  ownship.getLongitude()) * (plane.getLatitude() < ownship.getLatitude()? -1 : 1);
   float positionY = calcDistance(ownship.getLatitude(), plane.getLongitude(), ownship.getLatitude(),
                                  ownship.getLongitude()) * (plane.getLongitude() < ownship.getLongitude()? -1 : 1);

   float positionZ = plane.getAltitude()-ownship.getAltitude();

   Vector2d difference = Vector2d(positionX,positionY).normalized();
   std::cout << difference.x << "," << difference.y << std::endl;
   std::cout << ownship.getNorthVelocity() << "," << ownship.getEastVelocity() << std::endl;

   float angle = (float)acos((float)Vector2d::Dot(Vector2d(ownship.getNorthVelocity(),ownship.getEastVelocity()).normalized(),
                                        difference));
   //Angle offset
   //if 'difference' is to the left, use negabive bearings.
   float bearing = 180.f/M_PI * angle * (difference.x > 0 ? -1 : 1);



   TcasReport report;
   report.set_bearing(bearing);
   report.set_altitude(positionZ);

   report.set_range((float)sqrt(range*range + positionZ*positionZ/(NAUT_MILES_TO_FEET * NAUT_MILES_TO_FEET)));
   report.set_id(plane.getTcasId());
   return report;
}

void TcasSensor::sendData(const TestServerPlane &plane, const TestServerPlane & ownship) {
   this->getEndpoint().getSocket() << TcasSensor::createReport(plane, ownship);
}

TcasSensor::TcasSensor(SensorEndpoint *endpoint):
Sensor(endpoint){

}
