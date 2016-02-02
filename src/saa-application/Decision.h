//
// Created by jacrushar on 11/17/15.
//

#ifndef SAA_APPLICATION_DECISION_H
#define SAA_APPLICATION_DECISION_H

#include "common/protobuf/cdti.pb.h"
#include "SensorData.h"

class Decision
{
public:
   void report(std::vector<CDTIPlane *>* list, std::vector<SensorData>* planes, CDTIPlane::Severity* severity);
   CDTIReport * generateReport(std::vector<CDTIPlane *>* list, CDTIPlane* ownship, CDTIPlane::Severity* severity);
};
#endif //SAA_APPLICATION_DECISION_H
