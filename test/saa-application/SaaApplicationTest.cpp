//
// Created by jacrushar on 2/17/16.
//

#include <gtest/gtest.h>
#include <common/protobuf/adsb.pb.h>
#include <common/protobuf/cdti.pb.h>
#include <common/protobuf/ownship.pb.h>
#include <saa-application/SensorData.h>
#include <saa-application/SaaApplication.h>


TEST(saa_Test, adsbToRel) {
   AdsBReport adsb;
   OwnshipReport ownship;

   //initialize adsb
   adsb.set_tail_number("not needed");
   adsb.set_longitude(30.0);
   adsb.set_latitude(30.5);
   adsb.set_altitude(20000); // feet
   adsb.set_north(200); // ft/s
   adsb.set_east(0); // ft/s
   adsb.set_down(0); // ft/s

   //initialize ownship
   ownship.set_ownship_longitude(30.0);
   ownship.set_ownship_latitude(30.0);
   ownship.set_ownship_altitude(20000); // feet
   ownship.set_north(200); // ft/s
   ownship.set_east(0); // ft/s
   ownship.set_down(0); // ft/s

   SensorData result = SaaApplication::adsbToRelative(adsb, ownship);

   assert(result.getVelocity().x == 0);
   assert(result.getVelocity().y == 0);
   assert(result.getVelocity().z == 0);
   assert(result.getPurePosition().x >= 30.0216 - .05 && result.getPurePosition().x <= 30.0216 + .05);
   assert(result.getPurePosition().y == 0);
   assert(result.getPurePosition().z == 0);

   //now test longitude
   ownship.set_ownship_longitude(29.8);
   adsb.set_latitude(30.0);

   result = SaaApplication::adsbToRelative(adsb, ownship);

   assert(result.getPurePosition().y >= 10.399568 - .05 && result.getPurePosition().y <= 10.399568 + .05);
}