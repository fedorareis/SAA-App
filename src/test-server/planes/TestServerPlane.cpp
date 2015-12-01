//
// Created by Kyle Piddington on 12/1/15.
//

#include "TestServerPlane.h"

TestServerPlane::TestServerPlane():
latLongAlt(0,0,0),
northEastSouth(0,0,0),
motionPtr(nullptr)
{

}

TestServerPlane TestServerPlane::createPlaneAtTick(float tick)
{

}

void TestServerPlane::setAdsbEnabled(bool adsb) {

}

void TestServerPlane::setTcasEnabled(bool tcas) {

}

void TestServerPlane::setMotion(const Motion * m) {
   if(motionPtr != nullptr)
      delete  motionPtr;
   motionPtr = m->clone();
}

double TestServerPlane::getLatitude() const {
   return 0;
}

double TestServerPlane::getLongitude() const {
   return 0;
}

double TestServerPlane::getAltitude() const {
   return 0;
}

double TestServerPlane::getNorthVelocity() const{
   return 0;
}

double TestServerPlane::getEastVelocity() const{
   return 0;
}

double TestServerPlane::getDownVelocity() const{
   return 0;
}

bool TestServerPlane::getADSBEnabled() const {
   return false;
}

bool TestServerPlane::getTcasEnabled() const {
   return false;
}

TestServerPlane::~TestServerPlane() {
   if(motionPtr != nullptr)
      delete motionPtr;

}

void TestServerPlane::setTailNumber(std::string name) {
   this->tailNumber = name;

}
