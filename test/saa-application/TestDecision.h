//
// Created by Kyle Reis on 5/5/16.
//

#ifndef SAA_APPLICATION_TESTDECISION_H
#define SAA_APPLICATION_TESTDECISION_H

#include <saa-application/Decision.h>

class TestDecision : public Decision
{
public:
   using Decision::generateReport;

   using Decision::setSensitivityLevel;

   using Decision::calculateTAUMod;

   using Decision::calculateTCOA;

   using Decision::horizontalRA;

   using Decision::verticalRA;

   using Decision::tcasiiRA;

   using Decision::getSensitivity;
};


#endif //SAA_APPLICATION_TESTDECISION_H