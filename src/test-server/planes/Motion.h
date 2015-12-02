//
// Created by Kyle Piddington on 12/1/15.
//

#ifndef SAA_APPLICATION_MOTION_H
#define SAA_APPLICATION_MOTION_H
#define TICKS_PER_SECOND 1 //Linear mapping right now because i'm lazy ~kyle (apoligies)

#include "common/maths.h"
class Motion {
   public:
   virtual Vector3d getMotionAtTick(float tick) = 0;
   virtual Vector3d getVelocityAtTick(float tick) = 0;
   virtual Motion * clone() const = 0;

};


#endif //SAA_APPLICATION_MOTION_H
