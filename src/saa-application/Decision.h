/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
/**
 * The Decision class takes in all of the Correlated planes, determines the severity for each plane, and outputs a list
 * of all of the planes and their relevant data as a CDTIReport Protocal Buffer.
 *
 * @Author Kyle Reis 11/17/15
 */

#ifndef SAA_APPLICATION_DECISION_H
#define SAA_APPLICATION_DECISION_H

#include "CorrelatedData.h"

class Decision
{
public:
   /**
    * Calculates the Advisory for every plane in the airspace and returns the CDTIReport for all of them.
    * Advisory Levels: AIR, PROXIMATE, TRAFFIC, RESOLUTION, and CRASH
    *
    * @param planes The list of CorrelatedData that is passed from the Correlation module.
    * @param ownship The ownship.
    * @return The CDTIReport for all of the planes in planes.
    */
   CDTIReport* calcAdvisory(std::vector<CorrelatedData>* planes, SensorData* ownship);

   static void setTime0(time_t time);

private:
   static time_t time0;

protected:
   // The Sensativity Level (SL) based on altitude.
   int sensitivity;
   double tau;
   double tCOA;

   /**
    * Generates the CDTIReport to be sent to the CDTI and Validation.
    *
    * @param list The list of planes with their advisories set.
    * @param ownship The CDTIPlane version of the ownship.
    * @param severity The maximum severity for the planes in list.
    * @return The CDTIReport for all of the planes in planes.
    */
   CDTIReport* generateReport(std::vector<CDTIPlane *>* list, CDTIPlane* ownship, CDTIPlane::Severity* severity);

   /**
    * Calculates the Sensitivity Level as described page 10 of
    * https://drive.google.com/file/d/0BxXF9g8ajTSfOVgzX18xdEpCTjA/view?usp=sharing
    *
    * @param ownship The ownship data so that it can be used in calculating the sensitivity level.
    */
   void setSensitivityLevel(SensorData* ownship);

   /**
    * Calculates the Modified Tau as described in http://shemesh.larc.nasa.gov/people/cam/publications/gnc2013-draft.pdf
    * Tau is the time to Closest Point of Approach (CPA)
    *
    * @param plane The plane that we are calculating the Tau for.
    * @param RA Whether or not it is a Resolution Advisory (RA).
    * @return Tau
    */
   double calculateTAUMod(CorrelatedData plane, bool RA);

   /**
    * Calculates the Time to Co-Altitude as described in http://shemesh.larc.nasa.gov/people/cam/publications/gnc2013-draft.pdf
    *
    * @param plane The plane that we are calculating the Tau for.
    * @return time to Co-Altitude
    */
   double calculateTCOA(CorrelatedData plane);

   /**
    * Determines if a Horizontal Advisory should be issued as described in http://shemesh.larc.nasa.gov/people/cam/publications/gnc2013-draft.pdf
    *
    * @param plane The plane that we are calculating the Tau for.
    * @param RA Whether or not it is a Resolution Advisory (RA).
    * @return true if an advisory should be issued based on the Horizontal CPA
    */
   bool horizontalRA(CorrelatedData plane, bool RA);

   /**
    * Determines if a Vertical Advisory should be issued as described in http://shemesh.larc.nasa.gov/people/cam/publications/gnc2013-draft.pdf
    *
    * @param plane The plane that we are calculating the Tau for.
    * @param RA Whether or not it is a Resolution Advisory (RA).
    * @return true if an advisory should be issued based on the Horizontal CPA
    */
   bool verticalRA(CorrelatedData plane, bool RA);

   /**
    * Determines if an Advisory should be issued as described(mostly) in http://shemesh.larc.nasa.gov/people/cam/publications/gnc2013-draft.pdf
    * Read As: TCASII RA (TCAS 2 RA)
    *
    * @param plane The plane that we are calculating the Tau for.
    * @param RA Whether or not it is a Resolution Advisory (RA).
    * @param cpaRange The CPA range within which to issue an advisory.
    * @return true if an advisory should be issued based on the Horizontal CPA
    */
   bool tcasiiRA(CorrelatedData plane, bool RA, double cpaRange);

   int getSensitivity()
   {
      return sensitivity;
   }

   // Values for both arrays come from table on page 10 of https://drive.google.com/file/d/0BxXF9g8ajTSfOVgzX18xdEpCTjA/view?usp=sharing
   // Sensitivity levels start at 2 so arrays are padded with 0 for indeces 0 and 1.
   // DMOD is the Horizontal Threshold
   double DMOD_TA[9] = {0, 0, 0.30, 0.33, 0.48, 0.75, 1.00, 1.30, 1.30};
   double DMOD_RA[9] = {0, 0, 0, 0.20, 0.35, 0.55, 0.80, 1.10, 1.10};
   // TAU is the Time Threshold
   double TAU_TA[9] = {0, 0, 20, 25, 30, 40, 45, 48, 48};
   double TAU_RA[9] = {0, 0, 0, 15, 20, 25, 30, 35, 35};

};
#endif //SAA_APPLICATION_DECISION_H
