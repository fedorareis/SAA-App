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
// Created by Kyle Piddington on 11/28/15.
//

#include "OwnshipSensor.h"
#include "common/protobuf/ownship.pb.h"
OwnshipSensor::OwnshipSensor(SensorEndpoint * endpoint):
        Sensor(endpoint, false)
{

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
   report.set_ownship_altitude(plane.getAltitude() * NAUT_MILES_TO_FEET);
   report.set_north(plane.getNorthVelocity() * NAUT_MILES_TO_FEET);
   report.set_east(plane.getEastVelocity() * NAUT_MILES_TO_FEET);
   report.set_down(plane.getDownVelocity() * NAUT_MILES_TO_FEET);
   (this->getEndpoint().getSocket().operator<<(report));

}

