//
// Created by jacrushar on 11/17/15.
//

#include <iostream>
#include <fstream>
#include "math.h"
#include <common/Maths.h>
#include "Decision.h"

void Decision::report(std::vector<CDTIPlane *>* list, std::vector<CorrelatedData>* planes, CDTIPlane::Severity* severity)
{
   //std::cout << "We are making decisions here" << std::endl;

   list->clear();

   // Iterates over the list and assigns a Severity to it.
   for (std::vector<CorrelatedData>::iterator it = (*planes).begin(); it != (*planes).end(); ++it)
   {
      CDTIPlane* plane = it->getCDTIPlane();
      if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < .5 && fabs(it->getPosition().z) < 50)
      {
         // Should be AIR
         plane->set_severity(CDTIPlane::RESOLUTION);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 2 && fabs(it->getPosition().z) < 300)
      {
         plane->set_severity(CDTIPlane::RESOLUTION);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 5 && fabs(it->getPosition().z) < 500)
      {
         plane->set_severity(CDTIPlane::TRAFFIC);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 10 && fabs(it->getPosition().z) < 1000)
      {
         plane->set_severity(CDTIPlane::PROXIMATE);
      }
      else if(it->getPosition().distance(Vector3d(0,0,it->getPosition().z)) < 20 && fabs(it->getPosition().z) < 2000)
      {
         // Should be CRASH
         plane->set_severity(CDTIPlane::PROXIMATE);
      }

      list->push_back(plane);
   }

}

CDTIReport * Decision::generateReport(std::vector<CDTIPlane *>* list, CDTIPlane* ownship, CDTIPlane::Severity* severity)
{
   //std::cout << "We are generating the cdti report here" << std::endl;

   CDTIReport * report = new CDTIReport;

   report->set_advisorylevel(CDTIReport::PROXIMATE);
   report->set_advisorymessage("Move out of the way");
   report->set_allocated_ownship(ownship);
   report->set_timestamp(time(0));

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

void calculateCPA(CorrelatedData plane)
{

}