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
    Vector3d getVelocity() const;

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
   void setPlaneId(int pd);
   static int nextId();
   int getId() const;
private:
    static int idSeq;
   double t;
   Motion * motionPtr;
   Vector3d northEastDownVel;
    Vector3d latLongAlt;

   int tcasID;
   int radarID;
    int planeID;

   bool isADSBEnabled;
   bool isTCasEnabled;
   bool isRadarEnabled;

   std::string tailNumber;


};


#endif //SAA_APPLICATION_TESTSERVERPLANE_H
