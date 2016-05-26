//
// Created by Kyle Piddington on 2/2/16.
//

#include <iostream>
#include <test-server/TestServer.h>
#include <common/Vec3dNoise.h>
#include <common/FrameBody.h>
#include "RadarSensor.h"

RadarSensor::RadarSensor(SensorEndpoint *endpoint, bool jitter) :
        Sensor(endpoint, jitter)
{

}


/**
 * create a radar report from two planes,
 */

RadarReport RadarSensor::createReport(const TestServerPlane &plane, const TestServerPlane &ownship) {
   return createReport(plane, ownship, *TestServer::getRadarPositionNoise(), *TestServer::getRadarVelocityNoise());
}



RadarReport RadarSensor::createReport(const TestServerPlane &plane, const TestServerPlane &ownship,
   Vec3dNoise & positionDistribution, Vec3dNoise & velocityDistribution ) {
   RadarReport rept;
   //Create range from position
   auto lla = ownship.getLatLongAlt();
   auto ownshipbasis = makeBodyBasis(lla, ownship.getVelocity());
   FrameBody ownFrameB(lla, ownshipbasis);
   Vector3d P_BO_B = ownFrameB.tx(llaToXyz(plane.getLatLongAlt()));
   float range = (float)P_BO_B.getMagnitude();
   //Angle offset
   //if 'difference' is to the left, use negabive bearings.
   float azimuth = (float)radToDeg(atan2(P_BO_B.y,P_BO_B.x));
   float elevation = (float)tan( P_BO_B.z / std::sqrt(P_BO_B.y * P_BO_B.y + P_BO_B.x * P_BO_B.x));


   RadarReport report;

   //tuple of the position to send to report. is in format (range,azimuth,altitude)
   Vector3d finalPosition(range*FEET_TO_NAUT_MILES, azimuth, elevation);

   Vector3d velocity(plane.getNorthVelocity(),
                     plane.getEastVelocity(),
                     plane.getDownVelocity());
   if (jitter)
   {

      finalPosition += positionDistribution.getNoise();
      velocity += velocityDistribution.getNoise();
   }

   report.set_range(finalPosition.x);
   report.set_azimuth(finalPosition.y);
   report.set_elevation(finalPosition.z);
   report.set_north(velocity.x);
   report.set_east(velocity.y);
   report.set_down(velocity.z);
   report.set_longitude(ownship.getLongitude());
   report.set_latitude(ownship.getLatitude());
   report.set_altitude(ownship.getAltitude());
   report.set_id(plane.getRadarId());
   report.set_timestamp(plane.getTimestamp());

   return report;
}


void RadarSensor::sendData(const TestServerPlane &plane, const TestServerPlane &other) {
   getEndpoint().getSocket() << createReport(plane,other);
}
