//
// Created by Kyle Piddington on 2/2/16.
//

#include <iostream>
#include <test-server/TestServer.h>
#include "RadarSensor.h"

RadarSensor::RadarSensor(SensorEndpoint *endpoint, bool jitter) :
        Sensor(endpoint, jitter)
{

}
/**
 * create a radar report from two planes,
 */
RadarReport RadarSensor::createReport(const TestServerPlane &plane, const TestServerPlane &ownship) {
   RadarReport rept;
   //Create range from position
   float range = calcDistance(plane.getLatitude(),plane.getLongitude(),ownship.getLatitude(),ownship.getLongitude());
   float positionX = calcDistance(plane.getLatitude(), ownship.getLongitude(), ownship.getLatitude(),
                                  ownship.getLongitude()) * (plane.getLatitude() < ownship.getLatitude()? -1 : 1); //Difference N
   float positionY = calcDistance(ownship.getLatitude(), plane.getLongitude(), ownship.getLatitude(),
                                  ownship.getLongitude()) * (plane.getLongitude() < ownship.getLongitude()? -1 : 1); //Difference E

   float positionZ = plane.getAltitude()-ownship.getAltitude();

   Vector2d difference = Vector2d(positionX,positionY).normalized();
   Vector2d leftVec = Vector2d(-ownship.getEastVelocity(),ownship.getNorthVelocity()).normalized();

   float angle = (float)acos((float)Vector2d::Dot(Vector2d(ownship.getNorthVelocity(),ownship.getEastVelocity()).normalized(),
                                                  difference));
   bool negBearing = Vector2d::Dot(leftVec,difference) <= 0;
   //Angle offset
   //if 'difference' is to the left, use negabive bearings.
   float azimuth = 180.f/M_PI * angle * (negBearing ? -1 : 1);

   float elevation = 180.f/M_PI * atan2(positionZ/NAUT_MILES_TO_FEET,range);

   RadarReport report;

   //tuple of the position to send to report. is in format (range,azimuth,altitude)
   Vector3d finalPosition(range, azimuth, positionZ);
   if (jitter)
   {
      finalPosition = TestServer::scrambleRadar(finalPosition);
   }

   range = (float) sqrt(finalPosition.x * finalPosition.x + finalPosition.z * finalPosition.z / (NAUT_MILES_TO_FEET *
                                                                                                 NAUT_MILES_TO_FEET));

   report.set_altitude((float) finalPosition.z);
   report.set_range(range);
   report.set_azimuth(finalPosition.y);

   std::cout << "RDR" << azimuth << "," << elevation << "," << range << std::endl;

   report.set_altitude(finalPosition.z);
   report.set_elevation(elevation);
   report.set_range(range);
   report.set_north(plane.getNorthVelocity() - ownship.getNorthVelocity());
   report.set_east(plane.getEastVelocity() - ownship.getEastVelocity());
   report.set_down(plane.getDownVelocity() - ownship.getDownVelocity());
   report.set_longitude(ownship.getLongitude());
   report.set_latitude(ownship.getLatitude());
   report.set_altitude(ownship.getAltitude());
   report.set_id(plane.getRadarId());
   report.set_timestamp(plane.getTimestamp());

   std::cout << range << "," << azimuth <<  "," << elevation << std::endl;
   return report;
}




void RadarSensor::sendData(const TestServerPlane &plane, const TestServerPlane &other) {
   getEndpoint().getSocket() << createReport(plane,other);
}
