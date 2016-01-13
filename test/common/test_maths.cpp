//
// Created by Kyle Piddington on 1/12/16.
//
#include <gtest/gtest.h>
#include "common/Maths.h"
TEST(Math, fpsToNmph)
{
   EXPECT_FLOAT_EQ(180*KNOT_CONVERSION, fpsToNmph(180));
}