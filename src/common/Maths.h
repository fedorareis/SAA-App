//
// Created by jacrushar on 12/1/15.
//

#ifndef SAA_APPLICATION_MATHS_H
#define SAA_APPLICATION_MATHS_H

#include <cmath>
#include <string>
#include <glm/glm.hpp>

#define EARTH_RADIUS 3440.0
#define EQ_EARTH_RADIUS 3963.190592
#define POLAR_EARTH_RADIUS 3949.902764
#define KNOT_CONVERSION 0.592484
#define FEET_TO_NAUT_MILES 6076.12f
#define NAUT_MILES_TO_FEET 1 / FEET_TO_NAUT_MILES

struct Vector3d
{
   Vector3d(double x, double y, double z):
   x(x),
   y(y),
   z(z){}
   Vector3d operator* (double  rhs)
   {
      return Vector3d(x*rhs,y*rhs,z*rhs);
   }
   Vector3d & operator +=(const Vector3d & rhs)
   {
      this->x += rhs.x;
      this->y += rhs.y;
      this->z += rhs.z;
      return *this;
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

   double getMagnitude();
   std::string toString()
   {
       return "(" + std::to_string(x) + "," + std::to_string(y) + "," + "," + std::to_string(z) + ")";
   }
   static double Dot(Vector3d a, Vector3d b)
   {
      return a.x*b.x + a.y*b.y + a.z*b.z;
   }

    static Vector3d cross(Vector3d u, Vector3d v)
    {
       return Vector3d(u.y * v.z - u.z * v.y,u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
    }

    Vector3d normalized()
   {
       double recipLen = 1/sqrt(x*x + y*y + z*z);
       return Vector3d(x*recipLen, y*recipLen, z * recipLen);
   }
};


bool operator==(Vector3d lhs, Vector3d rhs);

struct Vector2d
{
   Vector2d():
      x(0),
      y(0)
   {}

   Vector2d(double x,double y):
         x(x),
         y(y)
   {}

   Vector2d normalized()
   {
      double recipLen = 1/sqrt(x*x+y*y);
      return Vector2d(x*recipLen, y*recipLen);
   }
   double length()
   {
      return sqrt(x*x+y*y);
   }

   static double Dot(Vector2d a, Vector2d b)
   {
      return a.x*b.x + a.y*b.y;
   }
   double x, y;

};

struct NEDBases
{
public:
    Vector3d north;
    Vector3d east;
    Vector3d down;
    NEDBases(Vector3d north, Vector3d east, Vector3d down):north(north),east(east),down(down){}
};

struct BodyBasis
{
    Vector3d forward;
    Vector3d right;
    Vector3d down;
    BodyBasis(Vector3d forward, Vector3d right, Vector3d down):forward(forward),right(right),down(down){}
};

NEDBases makeNEDBasis(Vector3d vec);
BodyBasis makeBodyBasis(Vector3d lla,Vector3d vel);

Vector3d getDifference(Vector3d latLongAlt1, Vector3d latLongAlt2);
float calcDistance(float lat1, float lon1, float lat2, float lon2, float alt);

inline float feetToNauticalMiles(float feet);

inline float nauticalMilesToFeet(float miles);

float fpsToNmph(float fps);
float bearingToRadians(float bearing);
inline double degToRad(double degrees){return degrees * M_PI / 180.0;}
inline double radToDeg (double degrees){return degrees * 180.0 / M_PI;}

Vector3d llaToXyz(Vector3d latLongAlt);
Vector3d xyzToLla(Vector3d latLongAlt);

#endif //SAA_APPLICATION_MATHS_H
