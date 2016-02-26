//
// Created by jacrushar on 11/17/15.
//

#ifndef SAA_APPLICATION_DECISION_H
#define SAA_APPLICATION_DECISION_H

#include "CorrelatedData.h"

class Decision
{
public:
   CDTIPlane::Severity calcAdvisory(std::vector<CDTIPlane *>* list, std::vector<CorrelatedData>* planes,
                                    SensorData* ownship);
   CDTIReport * generateReport(std::vector<CDTIPlane *>* list, CDTIPlane* ownship, CDTIPlane::Severity* severity);
   static void setTime0(time_t time);
private:
   static time_t time0;

   /**
    * Calculates the Sensitivity Level as described page 10 of
    * https://drive.google.com/file/d/0BxXF9g8ajTSfOVgzX18xdEpCTjA/view?usp=sharing
    *
    * @param ownship The ownship data so that it can be used in calculating the sensitivity level.
    */

   int SensativityLevel(SensorData* ownship);
   /**
    * Calculates the Modified Tau as described in http://shemesh.larc.nasa.gov/people/cam/publications/gnc2013-draft.pdf
    * Tau is the time to Closest Point of Approach (CPA)
    *
    * @param plane The plane that we are calculating the Tau for.
    * @param RA Whether or not it is a Rraffic Advisory (RA).
    * @param SL The Sensativity Level (SL) based on altitude.
    */
   double calculateTAUMod(CorrelatedData plane, bool RA, int SL);

   // Values for both arrays come from table on page 10 of https://drive.google.com/file/d/0BxXF9g8ajTSfOVgzX18xdEpCTjA/view?usp=sharing
   // Sensitivity levels start at 2 so array was padded with 0 for indeces 0 and 1.
   double DMOD_TA[9] = {0, 0, 0.30, 0.33, 0.48, 0.75, 1.00, 1.30, 1.30};
   double DMOD_RA[9] = {0, 0, 0, 0.20, 0.35, 0.55, 0.80, 1.10, 1.10};

};
#endif //SAA_APPLICATION_DECISION_H
