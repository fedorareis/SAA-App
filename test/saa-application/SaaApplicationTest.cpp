//
// Created by jacrushar on 2/17/16.
//

#include <gtest/gtest.h>
#include <common/protobuf/adsb.pb.h>
#include <common/protobuf/cdti.pb.h>
#include <common/protobuf/ownship.pb.h>


TEST(saa_Test, adsbToRel) {
   AdsBReport adsb;
   OwnshipReport ownship;

   // initialize only the fields we need, then call the function, then assert things
}