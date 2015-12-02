//
// Created by Kyle Piddington on 12/1/15.
//

#ifndef SAA_APPLICATION_MOTION_H
#define SAA_APPLICATION_MOTION_H
#define TICKS_PER_SECOND 1 //Linear mapping right now because i'm lazy ~kyle (apoligies)
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
   double x;
   double y;
   double z;

};
class Motion {
   public:
   virtual Vector3d getMotionAtTick(float tick) = 0;
   virtual Vector3d getVelocityAtTick(float tick) = 0;
   virtual Motion * clone() const = 0;

};


#endif //SAA_APPLICATION_MOTION_H
