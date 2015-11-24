//
// Created by Helen Hwang on 11/18/15.
//

#ifndef SAA_APPLICATION_TESTFILEPARSER_H
#define SAA_APPLICATION_TESTFILEPARSER_H

#include <iostream>
#include <fstream>
#include <exception>
#include <../lib/xml-parser/rapidxml.hpp>

/**
 * This class parses the XML file that contains one test case and validates
 * whether the file contains all necessary the configuration data.
 */
class TestFileParser{
   // ALWAYS initialize data members in the same order they are declared

public:
   TestFileParser(std::string file) : testFile(file){}; // constructor

   void load(); // loads the testFile to the parser
   // TestCase GetTestCase(); // returns the TestCase built from this file

private:
   std::string testFile;
   rapidxml::xml_document<> doc; // file iterator

   void buildTestCase(); // builds the test case
   void getOwnship(rapidxml::xml_node<> *node); // handles parsing data for ownship
   void getMovement(rapidxml::xml_node<> *node); // handles parsing data for movement
   bool isAttribute(rapidxml::xml_node<> *node, std::string attribute); // validates that attribute exists
   void getSensors(rapidxml::xml_node<> *node); // handles parsing sensors
   void getPlanes(rapidxml::xml_node<> *node); // handles parsing data for other planes
   bool isCoordinate(rapidxml::xml_node<> *node); // validates that all xyz coordinates exists
};

#endif //SAA_APPLICATION_TESTFILEPARSER_H
