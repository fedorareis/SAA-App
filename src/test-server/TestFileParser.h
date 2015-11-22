//
// Created by Helen Hwang on 11/18/15.
//

#ifndef SAA_APPLICATION_TESTFILEPARSER_H
#define SAA_APPLICATION_TESTFILEPARSER_H

#include <iostream>
#include <fstream>
#include <../lib/xml-parser/rapidxml.hpp>

/**
 * Include library for XML parsing
 *
 * This class parses the XML file that may contain multiple testsuit
 * which may contain multiple testcases.
 */
class TestFileParser{
   // ALWAYS initialize data members in the same order they are declared

public:
   TestFileParser(std::string file) : testFile(file){}; // constructor

   void load(); // loads the testFile to the parser
   // TestCase GetTestCase(); // returns the TestCase built from this file

private:
   std::string testFile;
   rapidxml::xml_document<> doc;

   void buildTestCase(); // builds the test case
   bool getOwnship(); // handles parsing data for ownship
   bool getPlanes(); // handles parsing data for other planes
};

#endif //SAA_APPLICATION_TESTFILEPARSER_H
