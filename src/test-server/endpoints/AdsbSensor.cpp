//
// Created by Kyle Piddington on 11/28/15.
//

#include "AdsbSensor.h"
#include <common/protobuf/adsb.pb.h>

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
   report.set_timestamp(plane.getTimestamp());
   report.set_latitude(plane.getLatitude());
   report.set_longitude(plane.getLongitude());
   report.set_altitude(plane.getAltitude());
   report.set_tail_number(plane.getTailNumber());
   report.set_north(plane.getNorthVelocity());
   report.set_east(plane.getEastVelocity());
   report.set_down(plane.getDownVelocity());

   this->getEndpoint().getSocket() << report;

}
