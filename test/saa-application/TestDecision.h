//
// Created by Kyle Reis on 5/5/16.
//

#ifndef SAA_APPLICATION_TESTDECISION_H
#define SAA_APPLICATION_TESTDECISION_H

#include <saa-application/Decision.h>

class TestDecision : public Decision
{
public:
   using Decision::generateReport(std::vector<CDTIPlane *>* list, CDTIPlane* ownship, CDTIPlane::Severity* severity);

   using Decision::setSensitivityLevel(SensorData* ownship);

   using Decision::calculateTAUMod(CorrelatedData plane, bool RA);

   using Decision::calculateTCOA(CorrelatedData plane);

   using Decision::horizontalRA(CorrelatedData plane, bool RA);

   using Decision::verticalRA(CorrelatedData plane, bool RA);

   using Decision::tcasiiRA(CorrelatedData plane, bool RA, double cpaRange);
};


#endif //SAA_APPLICATION_TESTDECISION_H