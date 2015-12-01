//
// Created by Kyle Piddington on 11/28/15.
//

#include "AdsbSensor.h"
#include <common/protobuf/adsb.pb.h>
//@TODO add configuration data for error here
AdsbSensor::AdsbSensor(SensorEndpoint * endpoint):
Sensor(endpoint)
{

}
void AdsbSensor::sendData(Plane & plane)
{
   AdsBReport report;
   //report.set_timestamp(plane.getTimestep());
   //report.set_latitude(plane.getLatitude());
   //report.set_longitude(plane.getLongitude());
   //report.set_altitude(plane.getAltitude());
   //report.set_tail_number(plane.getTailNumber());
   //report.set_north(plane.getNorth());
   //report.set_east(plane.getEast());
   //report.set_down(plane.getDown());
   (this->getEndpoint().getSocket().operator<<(report));

}