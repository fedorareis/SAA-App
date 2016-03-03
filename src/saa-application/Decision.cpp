//
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include <fstream>
#include "math.h"
#include <common/Maths.h>
#include "Decision.h"
time_t Decision::time0 = 0;

CDTIPlane::Severity Decision::calcAdvisory(std::vector<CDTIPlane *>* list, std::vector<CorrelatedData>* planes,
                                           SensorData* ownship)
{
   Decision::sensitivityLevel(ownship);
   CDTIPlane::Severity severity = CDTIPlane::PROXIMATE;

   list->clear();

   // Iterates over the list and assigns a Severity to it.
   for (std::vector<CorrelatedData>::iterator it = (*planes).begin(); it != (*planes).end(); ++it)
   {
      CDTIPlane* plane = it->getCDTIPlane();
      if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < .5 && fabs(it->getPosition().z) < 50 &&
         tcasiiRA(*it, true, 0.2))
      {
         // Should be CRASH
         // TODO: Implement CRASH enum in cdti proto
         plane->set_severity(CDTIPlane::RESOLUTION);
         severity = (CDTIPlane::Severity) (severity < CDTIPlane::RESOLUTION ? CDTIPlane::RESOLUTION : severity);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 2 && fabs(it->getPosition().z) < 300
              && tcasiiRA(*it, true, 0.5))
      {
         plane->set_severity(CDTIPlane::RESOLUTION);
         severity = (CDTIPlane::Severity) (severity < CDTIPlane::RESOLUTION ? CDTIPlane::RESOLUTION : severity);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 5 && fabs(it->getPosition().z) < 500
              && tcasiiRA(*it, false, 1))
      {
         plane->set_severity(CDTIPlane::TRAFFIC);
         severity = (CDTIPlane::Severity) (severity < CDTIPlane::TRAFFIC ? CDTIPlane::TRAFFIC : severity);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 10 && fabs(it->getPosition().z) < 1000)
      {
         plane->set_severity(CDTIPlane::PROXIMATE);
         severity = (CDTIPlane::Severity) (severity < CDTIPlane::PROXIMATE ? CDTIPlane::PROXIMATE : severity);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 20 && fabs(it->getPosition().z) < 2000)
      {
         // Should be AIR
         // TODO: Implement AIR enum in cdti proto
         plane->set_severity(CDTIPlane::PROXIMATE);
      }

      list->push_back(plane);
   }

}

CDTIReport * Decision::generateReport(std::vector<CDTIPlane *>* list, CDTIPlane* ownship, CDTIPlane::Severity* severity)
{

   CDTIReport * report = new CDTIReport;

   report->set_advisorylevel(CDTIReport::Severity(*severity));
   // TODO: Implement meaningful messages
   report->set_advisorymessage("Move out of the way");
   CDTIPlane * plane = new CDTIPlane();
   plane->CopyFrom(*ownship);
   report->set_allocated_ownship(plane);
   report->set_timestamp(time(0) - Decision::time0);

   // Iterates over the list adding planes to the Report for the CDTI
   for (std::vector<CDTIPlane *>::iterator it = (*list).begin(); it != (*list).end(); ++it)
   {
      CDTIPlane* planes = report->add_planes();
      planes->set_id((*it)->id());
      planes->set_allocated_velocity((*it)->mutable_velocity());
      planes->set_allocated_position((*it)->mutable_position());
      planes->set_severity((*it)->severity());
   }

   return report;
}

void Decision::setTime0(time_t time) {
   time0 = time;
}

void Decision::sensitivityLevel(SensorData* ownship)
{

   // Based on table on page 10 of https://drive.google.com/file/d/0BxXF9g8ajTSfOVgzX18xdEpCTjA/view?usp=sharing
   if (ownship->getPurePosition().z > 42000)
   {
      sensitivity = 7;
   }
   else if(ownship->getPurePosition().z > 20000)
   {
      sensitivity = 7;
   }
   else if(ownship->getPurePosition().z > 10000)
   {
      sensitivity = 6;
   }
   else if(ownship->getPurePosition().z > 5000)
   {
      sensitivity = 5;
   }
   else if(ownship->getPurePosition().z > 2350)
   {
      sensitivity = 4;
   }
   else if(ownship->getPurePosition().z > 1000)
   {
      sensitivity = 3;
   }
   else
   {
      sensitivity = 2;
   }
}

double Decision::calculateTAUMod(CorrelatedData plane, bool RA)
{
   Vector2d planePos = Vector2d(plane.getPosition().x, plane.getPosition().y);
   Vector2d planeVel = Vector2d(plane.getVelocity().x, plane.getVelocity().y);

   double DMOD = 0;

   if (RA)
   {
      DMOD = DMOD_RA[sensitivity];
   }
   else
   {
      DMOD = DMOD_TA[sensitivity];
   }

   double dot = Vector2d::Dot(planePos, planeVel);
   double magnitude = planePos.length();

   // DMOD is only 0 in cases where a RA shouldn't be issued or if the sensitivity is invalid.
   if (!DMOD)
   {
      return 0;
   }

   return ((DMOD * DMOD) - (magnitude * magnitude))/ dot;
}

double Decision::calculateTCOA(CorrelatedData plane)
{
   return -1 * (plane.getPosition().z / plane.getVelocity().z);
}

bool Decision::horizontalRA(CorrelatedData plane, bool RA)
{
   double dot = Vector3d::Dot(plane.getPosition(), plane.getVelocity());
   tau = calculateTAUMod(plane, RA);

   if (RA)
   {
      return (dot < 0 && tau <= TAU_RA[sensitivity]);
   }

   return (dot < 0 && tau <= TAU_TA[sensitivity]);
}

bool Decision::verticalRA(CorrelatedData plane, bool RA)
{
   double product = plane.getPosition().z * plane.getVelocity().z;
   tCOA = calculateTCOA(plane);

   if (RA)
   {
      return (product < 0 && tCOA <= TAU_RA[sensitivity]);
   }

   return (product < 0 && tCOA <= TAU_TA[sensitivity]);
}

bool Decision::tcasiiRA(CorrelatedData plane, bool RA, double cpaRange)
{
   bool vert = verticalRA(plane, RA);
   bool horz = horizontalRA(plane, RA);

   // treating the horizontal and vert time to CPA as the x and y of a right triangle and using the hypotenuse as the actual time to CPA
   double hypTime = sqrt((tau * tau) + (tCOA * tCOA));

   // I'm not sure if the physics/math on this are sound. d = tv but I am not sure how that works in 3d space with v as a vector
   double CPA = (plane.getVelocity() * hypTime).getMagnitude();

   return (vert || horz) && (CPA < cpaRange);
}