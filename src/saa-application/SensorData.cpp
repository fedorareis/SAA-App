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
