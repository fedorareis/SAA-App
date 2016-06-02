/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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

LinearMotion::LinearMotion(Vector3d initialPos, Vector3d velocity):
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
   return initialPos;
}
