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
   int sensitivity = Decision::SensativityLevel(ownship);
   CDTIPlane::Severity severity = CDTIPlane::PROXIMATE;

   list->clear();

   // Iterates over the list and assigns a Severity to it.
   for (std::vector<CorrelatedData>::iterator it = (*planes).begin(); it != (*planes).end(); ++it)
   {
      CDTIPlane* plane = it->getCDTIPlane();
      if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < .5 && fabs(it->getPosition().z) < 50 &&
         calculateTAUMod(*it, true, sensitivity) < 5)
      {
         // Should be CRASH
         // TODO: Implement CRASH enum in cdti proto
         plane->set_severity(CDTIPlane::RESOLUTION);
         severity = (CDTIPlane::Severity) (severity < CDTIPlane::RESOLUTION ? CDTIPlane::RESOLUTION : severity);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 2 && fabs(it->getPosition().z) < 300
              && calculateTAUMod(*it, true, sensitivity) < 30)
      {
         plane->set_severity(CDTIPlane::RESOLUTION);
         severity = (CDTIPlane::Severity) (severity < CDTIPlane::RESOLUTION ? CDTIPlane::RESOLUTION : severity);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 5 && fabs(it->getPosition().z) < 500
              && calculateTAUMod(*it, false, sensitivity) < 60)
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

   report->set_advisorylevel(CDTIReport::Severity(severity));
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

double Decision::calculateTAUMod(CorrelatedData plane, bool RA, int SL)
{
   Vector2d planePos = Vector2d(plane.getPosition().x, plane.getPosition().y);
   Vector2d planeVel = Vector2d(plane.getVelocity().x, plane.getVelocity().y);

   double DMOD = 0;

   if (RA)
   {
      DMOD = DMOD_RA[SL];
   }
   else
   {
      DMOD = DMOD_TA[SL];
   }

   double dot = Vector2d::Dot(planePos, planeVel);
   double magnitude = planePos.length();

   return ((DMOD * DMOD) - (magnitude * magnitude))/ dot;
}

int Decision::SensativityLevel(SensorData* ownship)
{
   int sensativity;

   // Based on table on page 10 of https://drive.google.com/file/d/0BxXF9g8ajTSfOVgzX18xdEpCTjA/view?usp=sharing
   if (ownship->getPurePosition().z > 42000)
   {
      sensativity = 7;
   }
   else if(ownship->getPurePosition().z > 20000)
   {
      sensativity = 7;
   }
   else if(ownship->getPurePosition().z > 10000)
   {
      sensativity = 6;
   }
   else if(ownship->getPurePosition().z > 5000)
   {
      sensativity = 5;
   }
   else if(ownship->getPurePosition().z > 2350)
   {
      sensativity = 4;
   }
   else if(ownship->getPurePosition().z > 1000)
   {
      sensativity = 3;
   }
   else
   {
      sensativity = 2;
   }

   return sensativity;
}