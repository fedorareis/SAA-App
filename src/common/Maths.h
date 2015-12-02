//
// Created by jacrushar on 12/1/15.
//

#ifndef SAA_APPLICATION_MATHS_H
#define SAA_APPLICATION_MATHS_H

#define EARTH_RADIUS 3440.0
struct Vector3d
{
   Vector3d(double x, double y, double z):
   x(x),
   y(y),
   z(z){}
   Vector3d operator* (float  rhs)
   {
      return Vector3d(x*rhs,y*rhs,z*rhs);
   }
   Vector3d operator- (const Vector3d & rhs)
   {
      return Vector3d(x - rhs.x, y - rhs.y, z - rhs.z);
   }
   double x;
   double y;
   double z;

};

#endif //SAA_APPLICATION_MATHS_H
