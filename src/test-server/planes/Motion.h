//
// Created by Kyle Piddington on 12/1/15.
//

#ifndef SAA_APPLICATION_MOTION_H
#define SAA_APPLICATION_MOTION_H

struct Vector3d
{
   Vector3d(double x, double y, double z):
   x(x),
   y(y),
   z(z){}
   double x;
   double y;
   double z;

};
class Motion {
   public:
   virtual Vector3d getMotionAtTick(float tick) = 0;
   virtual Motion * clone() const = 0;

};


#endif //SAA_APPLICATION_MOTION_H
