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
   TestServerPlane(const TestServerPlane & other);
   TestServerPlane& operator= (const TestServerPlane & rhs);
   ~TestServerPlane();

   /**
    * Create a test server plane at a different time.
    */
   void update(float dt);

   void setAdsbEnabled(bool adsb);
   void setTcasEnabled(bool tcas);
   void setMotion(const Motion & m);
   void setTailNumber(std::string name);
   void setLatLongAlt(Vector3d latLongAlt);
   void setNorthEastDownVelocity(Vector3d ned);

   float getLatitude() const;
   float getLongitude() const;
   float getAltitude() const;
   float getNorthVelocity() const;
   float getEastVelocity() const;
   float getDownVelocity() const;
   bool getADSBEnabled() const;
   bool getTcasEnabled() const;
   double getTimestamp() const;
   Motion * getMotion();
   std::string getTailNumber() const;
   private:
   double t;
   Motion * motionPtr;
   Vector3d northEastDownVel;
   Vector3d latLongAlt;


   bool isADSBEnabled;
   bool isTCasEnabled;
   std::string tailNumber;
};


#endif //SAA_APPLICATION_TESTSERVERPLANE_H
