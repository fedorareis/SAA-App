//
// Created by jacrushar on 11/17/15.
//

#include <iostream>
#include <fstream>
#include <common/Maths.h>
#include "common/protobuf/cdti.pb.h"
#include "Decision.h"

void Decision::report(std::vector<CDTIPlane *>* list, std::vector<Plane>* planes)
{
   //std::cout << "We are making decisions here" << std::endl;

   list->clear();
   for (std::vector<Plane>::iterator it = (*planes).begin(); it != (*planes).end(); ++it)
   {
      CDTIPlane* plane = it->getCDTIPlane();
      if(it->getPosition().distance(Vector3d(0,0,0)) < 3)
      {
         plane->set_severity(CDTIPlane::RESOLUTION);
      }
      else if(it->getPosition().distance(Vector3d(0,0,0)) < 5)
      {
         plane->set_severity(CDTIPlane::TRAFFIC);
      }
      else
      {
         plane->set_severity(CDTIPlane::PROXIMATE);
      }

      list->push_back(plane);
   }

}

CDTIReport * Decision::generateReport(std::vector<CDTIPlane *>* list, CDTIPlane* ownship)
{
   //std::cout << "We are generating the cdti report here" << std::endl;

   CDTIReport * report = new CDTIReport;

   report->set_advisorylevel(CDTIReport::PROXIMATE);
   report->set_advisorymessage("Move out of the way");
   report->set_allocated_ownship(ownship);
   report->set_timestamp(time(0));
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