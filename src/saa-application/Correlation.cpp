//
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include "Correlation.h"
#include "common/protobuf/adsb.pb.h"
#include "common/protobuf/ownship.pb.h"
#include "common/protobuf/radar.pb.h"
#include "common/protobuf/tcas.pb.h"

void Correlation::report()
{
   std::cout << "We are correlating some stuff" << std::endl;

   AdsBReport adsb;

   adsb.set_timestamp(0);
   adsb.set_latitude(1);
   adsb.set_longitude(2);
   adsb.set_altitude(3);
   adsb.set_tail_number("4");
   adsb.set_north(5);
   adsb.set_east(6);
   adsb.set_down(7);

   std::cout << adsb.timestamp() << std::endl;
}