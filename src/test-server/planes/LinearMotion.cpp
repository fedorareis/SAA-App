//
// Created by Kyle Piddington on 12/1/15.
//

#include "LinearMotion.h"

Vector3d LinearMotion::getMotionAtTick(float tick) {
   return velocity * (tick*TICKS_PER_SECOND);
}


LinearMotion * LinearMotion::clone() const {
   return new LinearMotion(*this);
}

LinearMotion::LinearMotion(const LinearMotion &other):
initialPos(other.initialPos),
velocity(other.velocity)
{

}

LinearMotion::LinearMotion(Vector3d intialPos, Vector3d velocity):
initialPos(initialPos),
velocity(velocity)
{

}

Vector3d LinearMotion::getVelocityAtTick(float tick) {
   return velocity;
}

LinearMotion::~LinearMotion() {

}

Vector3d LinearMotion::getInitialPosition() {
   return Vector3d(0, 0, 0);
}
