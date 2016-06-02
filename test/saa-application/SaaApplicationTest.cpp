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
// Created by jacrushar on 2/17/16.
//

#include <gtest/gtest.h>
#include <common/protobuf/adsb.pb.h>
#include <common/protobuf/cdti.pb.h>
#include <common/protobuf/ownship.pb.h>
#include <saa-application/SensorData.h>
#include <saa-application/SaaApplication.h>


TEST(saa_Test, adsbToRel)
{
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

   ASSERT_EQ(result.getVelocity().x, 0);
   ASSERT_EQ(result.getVelocity().y, 0);
   ASSERT_EQ(result.getVelocity().z, 0);
   ASSERT_GE(result.getPurePosition().x, 30.02 - .05);
   ASSERT_LE(result.getPurePosition().x, 30.02 + .05);
   ASSERT_EQ(result.getPurePosition().y, 0);
   ASSERT_EQ(result.getPurePosition().z, 0);

   //now test longitude
   ownship.set_ownship_longitude(29.8);
   adsb.set_latitude(30.0);

   result = SaaApplication::adsbToRelative(adsb, ownship);

   ASSERT_EQ(result.getVelocity().x, 0);
   ASSERT_EQ(result.getVelocity().y, 0);
   ASSERT_EQ(result.getVelocity().z, 0);
   ASSERT_EQ(result.getPurePosition().x, 0);
   ASSERT_GE(result.getPurePosition().y, 10.39 - .05);
   ASSERT_LE(result.getPurePosition().y, 10.39 + .05);
   ASSERT_EQ(result.getPurePosition().z, 0);
}

TEST(saa_Test, radarToRelative) {
   RadarReport radar;
   OwnshipReport ownship;

   //initialize radar report
   radar.set_range(12152.2); // 2 nautical miles
   radar.set_azimuth(0);
   radar.set_elevation(0);
   radar.set_north(200);
   radar.set_east(0);
   radar.set_down(0);

   //initialize ownship
   ownship.set_ownship_longitude(30.0);
   ownship.set_ownship_latitude(30.0);
   ownship.set_ownship_altitude(20000); // feet
   ownship.set_north(200); // ft/s
   ownship.set_east(0); // ft/s
   ownship.set_down(0); // ft/s

   SensorData result = SaaApplication::radarToRelative(radar, ownship);

   ASSERT_EQ(result.getVelocity().x, 0);
   ASSERT_EQ(result.getVelocity().y, 0);
   ASSERT_EQ(result.getVelocity().z, 0);
   std::cout << result.getPurePosition().x << std::endl;

   ASSERT_GE(result.getPurePosition().x, 2 - .05);
   ASSERT_LE(result.getPurePosition().x, 2 + .05);
   ASSERT_GE(result.getPurePosition().y, 0 - .05);
   ASSERT_LE(result.getPurePosition().y, 0 + .05);
   ASSERT_EQ(result.getPurePosition().z, 0);
}