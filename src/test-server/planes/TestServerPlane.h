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
   void setRadarEnabled(bool radar);
   void setMotion(const Motion & m);

   void setTailNumber(std::string name);
   void setLatLongAlt(Vector3d latLongAlt);
   void setNorthEastDownVelocity(Vector3d ned);


   float getLatitude() const;
   float getLongitude() const;
   float getAltitude() const;
   const Vector3d& getLatLongAlt() const;
   float getNorthVelocity() const;
   float getEastVelocity() const;
   float getDownVelocity() const;

   bool getRadarEnabled() const;
   bool getADSBEnabled() const;
   bool getTcasEnabled() const;
   double getTimestamp() const;
   Motion * getMotion();
   std::string getTailNumber() const;

   int getTcasId() const;
   int getRadarId() const;
   void setTcasId(int tc);
   void setRadarId(int rd);

private:
   double t;
   Motion * motionPtr;
   Vector3d northEastDownVel;
    Vector3d latLongAlt;

   int tcasID;
   int radarID;

   bool isADSBEnabled;
   bool isTCasEnabled;
   bool isRadarEnabled;

   std::string tailNumber;


};


#endif //SAA_APPLICATION_TESTSERVERPLANE_H
