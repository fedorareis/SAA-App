//
// Created by Kyle Piddington on 11/28/15.
//

#include "AdsbSensor.h"
#include <common/protobuf/adsb.pb.h>
#include <test-server/TestServer.h>

//@TODO add configuration data for error here
AdsbSensor::AdsbSensor(SensorEndpoint * endpoint, bool jitter):
Sensor(endpoint,jitter)
{


}
/**
 * ADSB doesn't acutally use the ownship
 * @TODO Refactor this!
 */
void AdsbSensor::sendData(const TestServerPlane & plane, const TestServerPlane & ownship)
{
   AdsBReport report;
   //format: (latitude, longitude, altitude)
   Vector3d finalPosition(plane.getLatLongAlt());
   if (jitter)
   {
      finalPosition = TestServer::scrambleADSB(finalPosition);
   }

   report.set_timestamp(plane.getTimestamp());
   report.set_latitude(finalPosition.x);
   report.set_longitude(finalPosition.y);
   report.set_altitude(finalPosition.z);
   report.set_tail_number(plane.getTailNumber());
   report.set_north(plane.getNorthVelocity());
   report.set_east(plane.getEastVelocity());
   report.set_down(plane.getDownVelocity());
   report.set_plane_id(plane.getId());

   this->getEndpoint().getSocket() << report;

}
