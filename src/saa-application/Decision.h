//
// Created by jacrushar on 11/17/15.
//

#ifndef SAA_APPLICATION_DECISION_H
#define SAA_APPLICATION_DECISION_H

#include "CorrelatedData.h"

class Decision
{
public:
   void calcAdvisory(std::vector<CDTIPlane *>* list, std::vector<CorrelatedData>* planes,
               CDTIPlane::Severity* severity, SensorData* ownship);
   CDTIReport * generateReport(std::vector<CDTIPlane *>* list, CDTIPlane* ownship, CDTIPlane::Severity* severity);
   static void setTime0(time_t time);
private:
   static time_t time0;
};
#endif //SAA_APPLICATION_DECISION_H
