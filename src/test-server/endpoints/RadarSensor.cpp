//
// Created by Kyle Piddington on 2/2/16.
//

#include <iostream>
#include "RadarSensor.h"

RadarSensor::RadarSensor(SensorEndpoint *endpoint):
Sensor(endpoint)
{

}
/**
 * create a radar report from two planes,
 */
RadarReport RadarSensor::createReport(const TestServerPlane &plane, const TestServerPlane &ownship) {
   RadarReport rept;
   //Create range from position
   float range = calcDistance(plane.getLatitude(),plane.getLongitude(),ownship.getLatitude(),ownship.getLongitude());
   float positionX = calcDistance(plane.getLatitude(), ownship.getLatitude(), ownship.getLatitude(),
                                  ownship.getLongitude()) * (plane.getLatitude() < ownship.getLatitude()? -1 : 1);
   float positionY = calcDistance(ownship.getLatitude(), plane.getLongitude(), ownship.getLatitude(),
                                  ownship.getLongitude()) * (plane.getLongitude() < ownship.getLongitude()? -1 : 1);

   float positionZ = plane.getAltitude()-ownship.getAltitude();

   Vector2d difference = Vector2d(positionX,positionY).normalized();

   float angle = (float)acos((float)Vector2d::Dot(Vector2d(ownship.getNorthVelocity(),ownship.getEastVelocity()).normalized(),
                                                  difference));
   //Angle offset
   //if 'difference' is to the left, use negabive bearings.
   float azimuth = 180.f/M_PI * angle * (difference.x > 0 ? -1 : 1);
   float elevation = 180.f/M_PI * atan2(positionZ/NAUT_MILES_TO_FEET,range);
   range = (float)sqrt(range*range + positionZ*positionZ/(NAUT_MILES_TO_FEET * NAUT_MILES_TO_FEET));

   RadarReport report;



   report.set_azimuth(azimuth);
   report.set_altitude(positionZ);
   report.set_elevation(elevation);
   report.set_range(range);
   report.set_north(plane.getNorthVelocity() - ownship.getNorthVelocity());
   report.set_east(plane.getEastVelocity() - ownship.getEastVelocity());
   report.set_down(plane.getDownVelocity() - ownship.getDownVelocity());
   report.set_longitude(ownship.getLongitude());
   report.set_latitude(ownship.getLatitude());
   report.set_altitude(ownship.getAltitude());


   return report;
}




void RadarSensor::sendData(const TestServerPlane &plane, const TestServerPlane &other) {
   getEndpoint().getSocket() << createReport(plane,other);
}
