//
// Created by Hae Ri Hwang on 11/24/15.
//

#include <math.h>
#include <iostream>
#include "TestCase.h"
#include "common/Maths.h"
TestCase::TestCase() :
ownship(TestServerPlane())
{

}

void TestCase::setName(const std::string name) {
   this->name = name;
}

void TestCase::setOwnship(const TestServerPlane & newPlane) {
   ownship = newPlane;
}

void TestCase::addPlane(const TestServerPlane & newPlane) {
   otherPlanes.push_back(TestServerPlane(newPlane));

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
TestServerPlane TestCase::getOwnship() {
   return ownship;
}

const std::vector<TestServerPlane> & TestCase::getPlanes() {
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
         std::cout << "Other plane at " << plane->getLatitude() << " " << plane->getLongitude() << " " << plane->getAltitude() << std::endl;

      }
   }
}

void TestCase::setTotalTime(float totalTime) {
   this->t = totalTime;
}

bool TestCase::isRunning() {
   return t > 0;
}
