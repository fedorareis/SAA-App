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
// Created by Kyle Reis on 11/19/15.
//

#include "SensorData.h"

CDTIPlane* SensorData::getCDTIPlane()
{
   severity = CDTIPlane::PROXIMATE;
   plane->Clear();
   plane->set_id(tailNumber);
   plane->set_severity(severity);
   plane->set_allocated_position(position);
   plane->set_allocated_velocity(velocity);
   plane->add_planetags(planeTag);

   return plane;
}

void SensorData::printPos() {
   //printf("tailNumber %s\n", tailNumber);
   printf("position x %f\n", position->x()); // north
   printf("position y %f\n", position->y()); // east
   printf("position z %f\n", position->z()); // down
   printf("velocity x %f\n", velocity->x()); // north
   printf("velocity y %f\n", velocity->y()); // east
   printf("velocity z %f\n", velocity->z()); // down
}
