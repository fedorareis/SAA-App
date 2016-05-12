//
// Created by Hae Ri Hwang on 11/24/15.
//

#include <math.h>
#include <iostream>
#include "TestCase.h"

TestCase::TestCase() :
ownship(TestServerPlane()),
radarId(0),
tcasId(0)
{

}

void TestCase::setName(const std::string name) {
   this->name = name;
}

void TestCase::setOwnship(const TestServerPlane & newPlane) {
   ownship = newPlane;
}

void TestCase::addPlane(const TestServerPlane & newPlane) {
   otherPlanes.push_back(newPlane);

}
void TestCase::update(float dt)
{
   t -= dt;
   ownship.update(dt);
   for(auto i = otherPlanes.begin(); i != otherPlanes.end(); i++)
   {
      i->update(dt);
   }
}
const TestServerPlane & TestCase::getOwnship()const
{
   return ownship;
}

const std::vector<TestServerPlane> & TestCase::getPlanes() const {
   return otherPlanes;
}

void TestCase::complete() {
   ownship.setLatLongAlt(Vector3d(0,0,ownship.getMotion()->getInitialPosition().z));
   for(auto plane = otherPlanes.begin(); plane != otherPlanes.end(); plane++)
   {
      if(plane->getMotion() != nullptr)
      {
         Vector3d relPos = plane->getMotion()->getInitialPosition();

         Vector3d diffPos = relPos - ownship.getMotion()->getInitialPosition();

         //Offset by lat and long miles (This should be encapsulated somewhere else)
         float newLat = ownship.getLatitude()   + diffPos.x / ((M_PI  * 2 * EARTH_RADIUS)/360.0); //Arc length, nMi/theta
         float newLong = ownship.getLongitude() + diffPos.y / ((M_PI  * 2 * EARTH_RADIUS)/360.0);
         plane->setLatLongAlt(Vector3d(newLat,newLong,relPos.z + ownship.getAltitude()));
         plane->setNorthEastDownVelocity(plane->getMotion()->getVelocityAtTick(0));

      }
   }
}

void TestCase::setTotalTime(float tTime) {
   this->t = tTime;
   this->totalTime = tTime;
}

bool TestCase::isRunning() {
   return t > 0;
}

int TestCase::getNextTcasId()
{
   return tcasId++;
}
int TestCase::getNextRadarId()
{
   return radarId++;
}

TestCase::TestCase(const TestCase &otherTestCase) :
        t(otherTestCase.t),
        name(otherTestCase.name),
        radarId(otherTestCase.radarId),
        tcasId(otherTestCase.tcasId),
        totalTime(otherTestCase.totalTime),
        enableErrors(otherTestCase.enableErrors)
{
   ownship = TestServerPlane(otherTestCase.ownship);
   for (auto plane: otherTestCase.otherPlanes)
      otherPlanes.push_back(plane);
}

void TestCase::makeDataNoise(bool noise)
{
   enableErrors = noise;
}


int TestCase::getTotalTime() const {
   return this->totalTime;
}

int TestCase::getElapsedTime() const {
   return getTotalTime() - t;
}

bool TestCase::getNoiseEnabled() const {
   return enableErrors;
}
