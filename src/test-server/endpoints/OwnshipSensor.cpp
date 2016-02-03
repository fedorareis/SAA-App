//
// Created by Kyle Piddington on 11/28/15.
//

#include "OwnshipSensor.h"
#include "common/protobuf/ownship.pb.h"
OwnshipSensor::OwnshipSensor(SensorEndpoint * endpoint):
Sensor(endpoint){

}
/**
 *  required sfixed64 timestamp = 1; // time of report
    required sfixed32 ownship_latitude = 2; // ownship latitude
    required sfixed32 ownship_longitude = 3; // ownship longitude
    required sfixed32 ownship_altitude = 4; // ownship GPS altitude
    required float north = 5; // ownship velocity north
    required float east = 6; // ownship velocity east
    required float down = 7; // ownship velocity down
 */
/**
 * Bit of a strange interface, since both planes are ownship.
 * @TODO Refactor this!
 */
void OwnshipSensor::sendData(const TestServerPlane & plane, const TestServerPlane & ownship)
{
   OwnshipReport report;
   report.set_timestamp((long)plane.getTimestamp());
   report.set_ownship_latitude(plane.getLatitude());
   report.set_ownship_longitude(plane.getLongitude());
   report.set_ownship_altitude(plane.getAltitude());
   report.set_north(plane.getNorthVelocity());
   report.set_east(plane.getEastVelocity());
   report.set_down(plane.getDownVelocity());
   (this->getEndpoint().getSocket().operator<<(report));

}

