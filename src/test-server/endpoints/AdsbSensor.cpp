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
