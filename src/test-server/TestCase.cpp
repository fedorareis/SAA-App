//
// Created by Hae Ri Hwang on 11/24/15.
//

#include "TestCase.h"

TestCase::TestCase() {

}

void TestCase::setName(const std::string name) {

}

void TestCase::setOwnship(const TestServerPlane &plane) {

}

void TestCase::addPlane(const TestServerPlane &plane) {

}

TestServerPlane TestCase::getOwnshipAtTick(float tick) {
   return TestServerPlane();
}

std::vector<TestServerPlane> TestCase::getPlanesAtTick(float tick) {
   return std::vector<TestServerPlane>();
}
