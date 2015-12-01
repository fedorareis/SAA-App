//
// Created by Kyle Piddington on 12/1/15.
//

#include "LinearMotion.h"

Vector3d LinearMotion::getMotionAtTick(float tick) {
   return Vector3d(0, 0, 0);
}


LinearMotion * LinearMotion::clone() const {
   return new LinearMotion(*this);
}

LinearMotion::LinearMotion(const LinearMotion &other):
velocity(other.velocity){

}

LinearMotion::LinearMotion(Vector3d velocity):
velocity(velocity)
{

}
