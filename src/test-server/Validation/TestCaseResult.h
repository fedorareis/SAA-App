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
