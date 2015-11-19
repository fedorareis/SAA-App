//
// Created by Helen Hwang on 11/18/15.
//

#ifndef SAA_APPLICATION_TESTFILEPARSER_H
#define SAA_APPLICATION_TESTFILEPARSER_H

#include <iostream>
/**
 * Include library for XML parsing
 *
 * This class parses the XML file that may contain multiple testsuit
 * which may contain multiple testcases.
 */
class TestFileParser{
   // ALWAYS initialize data members in the same order they are declared

public:
   TestFileParser(std::string file) : testFile(file){std::cout << "Hello from TestParser"<<std::endl;}; // constructor
   void load();
   // TestCase GetTestCase(); // returns the TestCase built from this file

private:
   std::string testFile;

   void buildTestCase(); // builds each test case
   void getOwnship(); // handles parsing data for ownship
   void getPlanes(); // handles parsing data for other planes
};

#endif //SAA_APPLICATION_TESTFILEPARSER_H
