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
//
// Created by Kyle Piddington on 1/19/16.
//

#ifndef SAA_APPLICATION_TESTCASERESULT_H
#define SAA_APPLICATION_TESTCASERESULT_H
#include <string>
#include <vector>
#include <common/protobuf/cdti.pb.h>
#include <common/Maths.h>


/**
 * A ResultPlane contains easier to access information from a CDTI plane message
 */

class ResultPlane
{
   public:
   /*
    * Construct a default result plane
    */
   ResultPlane();

   /*
    * Create a result plane from a google protobuf message
    * @msg the message to construct from
    */
   static ResultPlane fromGoogleProtobuf(const CDTIPlane & msg);
   /**
    * Get the ownship-ned position of the plane
    * @return a position (in miles) relative to the ownship's world position
    */
   Vector3d getPosition() const ;

   /**
    * Get the velocity of the plane, in ned coordinates
    * @return a velocity vector
    */
   Vector3d getVelocity() const;
   /**
    * Get the plane's tag
    */
   std::string getTag() const;
   /**
    * Get the plane severity
    */
   CDTIPlane_Severity getSeverity() const;

   private:
   Vector3d relativePosition;
   Vector3d nedVelocity;
   std::vector<int> planeTags;
   std::string tag;
   CDTIPlane_Severity severity;

};

class TestCaseResult {

   public:
   const std::vector<ResultPlane> & getPlanes(){return planes;}
   static TestCaseResult fromGoogleProtobuf(const CDTIReport & msg);

   long getTime() const;

   private:

   long time;
   std::vector<ResultPlane> planes;
   ResultPlane ownship;

};


#endif //SAA_APPLICATION_TESTCASERESULT_H
