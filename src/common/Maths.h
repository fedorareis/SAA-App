//
// Created by jacrushar on 12/1/15.
//

#ifndef SAA_APPLICATION_MATHS_H
#define SAA_APPLICATION_MATHS_H

#include <math.h>

#define EARTH_RADIUS 3440.0
#define KNOT_CONVERSION 0.592484

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
    double north(){return x;}
    double east(){return y;}
    double down(){return z;}
    double latitude(){return x;}
    double longitude(){return y;}
    double altitude(){return z;}
   Vector3d operator- (const Vector3d & rhs)
   {
      return Vector3d(x - rhs.x, y - rhs.y, z - rhs.z);
   }
   double distance(const Vector3d & other)
   {
      return sqrt((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y) + (other.z-z)*(other.z-z));
   }
   double x;
   double y;
   double z;

};

float calcDistance(float lat1, float lon1, float lat2, float lon2);

float fpsToNmph(float fps);

#endif //SAA_APPLICATION_MATHS_H
