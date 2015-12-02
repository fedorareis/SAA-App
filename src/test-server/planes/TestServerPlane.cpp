//
// Created by Kyle Piddington on 12/1/15.
//

#include <math.h>
#include "TestServerPlane.h"

Vector3d addToLatitudeLongitude(Vector3d latLongAlt, Vector3d translation)
{
   const float R = 20.9e6; //Radius of earth in feet.
   const float ft2Deg = 2*M_PI*R/360.0;
   //Convert N and E into angle rotations
   float dLat = translation.x;
   float dLong = translation.y;
   float dAlt = translation.z;
   Vector3d finalVector = latLongAlt;
   finalVector.z += translation.z; //Already in feet
   finalVector.x += dLat / ft2Deg; //(in ft, convert to angle)
   finalVector.y += dLong / ft2Deg; //(@TODO make this not actually just plane wrong (Badumchi i hate myself))
   return finalVector;
}

TestServerPlane::TestServerPlane():
      t(0),
      latLongAlt(0,0,0),
northEastDownVel(0,0,0),
motionPtr(nullptr)

{

}


//Actually move the plane (Can't do LatLongAlt from dNES)
void TestServerPlane::move(float dT)
{
   t+=dT;
   Vector3d translation = this->motionPtr->getVelocityAtTick(t) * dT;
   this->latLongAlt = addToLatitudeLongitude(latLongAlt,translation); //in (ft/sec)
   this->northEastDownVel = this->motionPtr->getVelocityAtTick(t);

}

void TestServerPlane::setAdsbEnabled(bool adsb) {
   this->isADSBEnabled = adsb;
}

void TestServerPlane::setTcasEnabled(bool tcas) {
   this->isTCasEnabled = tcas;
}

void TestServerPlane::setMotion(const Motion * m) {
   if(motionPtr != nullptr)
      delete  motionPtr;
   motionPtr = m->clone();
}

double TestServerPlane::getLatitude() const {
   return this->latLongAlt.x;
}

double TestServerPlane::getLongitude() const {
   return this->latLongAlt.y;
}

double TestServerPlane::getAltitude() const {
   return this->latLongAlt.z;
}

double TestServerPlane::getNorthVelocity() const{
   return this->northEastDownVel.x;
}

double TestServerPlane::getEastVelocity() const{
   return this->northEastDownVel.y;
}

double TestServerPlane::getDownVelocity() const{
   return this->northEastDownVel.z;
}

bool TestServerPlane::getADSBEnabled() const {
   return this->isADSBEnabled;
}

bool TestServerPlane::getTcasEnabled() const {
   return this->isTCasEnabled;
}

TestServerPlane::~TestServerPlane() {
   if(motionPtr != nullptr)
      delete motionPtr;

}

void TestServerPlane::setTailNumber(std::string name) {
   this->tailNumber = name;

}
std::string TestServerPlane::getTailNumber() const {
   return this->tailNumber;
}
