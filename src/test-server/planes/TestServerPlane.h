//
// Created by Kyle Piddington on 12/1/15.
//

#ifndef SAA_APPLICATION_TESTSERVERPLANE_H
#define SAA_APPLICATION_TESTSERVERPLANE_H


#include "Motion.h"
#include <string>

class TestServerPlane {
   public:
   TestServerPlane();
   ~TestServerPlane();

   /**
    * Create a test server plane at a different time.
    */
   void move(float dt);

   void setAdsbEnabled(bool adsb);
   void setTcasEnabled(bool tcas);
   void setMotion(const Motion * m);
   void setTailNumber(std::string name);

   double getLatitude() const;
   double getLongitude() const;
   double getAltitude() const;
   double getNorthVelocity() const;
   double getEastVelocity() const;
   double getDownVelocity() const;
   bool getADSBEnabled() const;
   bool getTcasEnabled() const;
   std::string getTailNumber() const;
   private:
   float t;
   Motion * motionPtr;
   Vector3d northEastDownVel;
   Vector3d latLongAlt;

   bool isADSBEnabled;
   bool isTCasEnabled;
   std::string tailNumber;
};


#endif //SAA_APPLICATION_TESTSERVERPLANE_H
