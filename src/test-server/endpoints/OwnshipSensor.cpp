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
void OwnshipSensor::sendData(Plane & plane)
{
   OwnshipReport report;
   (this->getEndpoint().getSocket().operator<<(report));

}

