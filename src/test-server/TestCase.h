//
// Created by Hae Ri Hwang on 11/24/15.
//

#ifndef SAA_APPLICATION_TESTCASE_H
#define SAA_APPLICATION_TESTCASE_H


#include <iosfwd>
#include <test-server/planes/TestServerPlane.h>
#include <vector>

class TestCase {

public:
   TestCase();
   /**
    * Set the name of the test case
    */
   void setName(const std::string name);
   /**
    * Set the ownship data of the test case
    */
   void setOwnship(const TestServerPlane & plane);
   /**
    * Add a plane to the test case
    */
   void addPlane(const TestServerPlane & plane);
   /**
    * Retreieve the ownship a a certain time (1 tick = 10seconds)
    */
   TestServerPlane getOwnshipAtTick(float tick);
   /**
    * Retrieve all the planes at a certain time(1 tick = 10 seconds)
    */
   std::vector<TestServerPlane> getPlanesAtTick(float tick);
};


#endif //SAA_APPLICATION_TESTCASE_H
