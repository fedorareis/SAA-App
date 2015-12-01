//
// Created by jacrushar on 11/17/15.
//

#ifndef SAA_APPLICATION_DECISION_H
#define SAA_APPLICATION_DECISION_H

#include "common/protobuf/cdti.pb.h"

class Decision
{
public:
   void report(std::vector<CDTIPlane *>* list);
   CDTIReport * generateReport(std::vector<CDTIPlane *>* list);
};
#endif //SAA_APPLICATION_DECISION_H
