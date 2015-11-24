//
// Created by Kyle Reis on 11/19/15.
//

#include "plane.h"

CDTIPlane Plane::getCDTIPlane()
{
   severity = CDTIPlane::PROXIMATE;

   plane.set_id(tailNumber);
   plane.set_severity(severity);
   plane.set_allocated_position(position);
   plane.set_allocated_velocity(velocity);

   return plane;
}