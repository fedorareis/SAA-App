//
// Created by Kyle Piddington on 1/12/16.
//
#include <gtest/gtest.h>
#include "common/Maths.h"
TEST(Math, fpsToNmph)
{
   EXPECT_FLOAT_EQ(180*KNOT_CONVERSION, fpsToNmph(180));
}
TEST(Vector2, len)
{
   EXPECT_FLOAT_EQ(sqrt(4+9), Vector2d(2,3).length());
}
TEST(Vector2, dot)
{
   Vector2d a(0,1);
   Vector2d b(1,1);
   EXPECT_FLOAT_EQ(1, Vector2d::Dot(a,b));
   b = b.normalized();
   EXPECT_FLOAT_EQ(sqrt(1/2.0), Vector2d::Dot(a,b));
   a = Vector2d(1,0);
   b = Vector2d(0,1);
   EXPECT_FLOAT_EQ(0, Vector2d::Dot(a,b));

   a = Vector2d(1,0);
   b = Vector2d(1,0);
   EXPECT_FLOAT_EQ(1, Vector2d::Dot(a,b));

}
TEST(Vector3, add)
{
   Vector3d a(1,2,3);
   Vector3d b(4,5,6);
   a += b;
   EXPECT_EQ(a.x, 5);
   EXPECT_EQ(a.y, 7);
   EXPECT_EQ(a.z, 9);


}
