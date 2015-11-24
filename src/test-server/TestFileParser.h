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
 * Includes error codes in configuration;
 * Possibly add more in the future
 */
enum ErrorCode
{
   success=0,
   os_tagErr, // =1 missing tag
   os_sensorErr, // =2 missing sensor
   os_mvntErr, // =3 missing direction
   os_posErr, // =4 missing position
   os_missingErr, // =5 missing ownship data
   p_tagErr, // =6 incoming plane missing tag
   p_sensorErr, // =7 incoming plane missing sensor
   p_mvntErr, // =8 incoming plane missing direction
   p_posErr, // =9 incoming plane missing position
   sensorError, // =10 missing all the sensor
   movementError, // =11 missing movement
   missingTypeErr, // =12 missing movement type
   positionError, // =13 missing position
   directionError, // =14 missing direction
   coordMissingErr, // =15 one of xyz value is missing
   testMissingError // =16 test tag is missing on the test
};

/**
 * This class parses the XML file that contains one test case and validates
 * whether the file contains all necessary the configuration data.
 *
 * Throws Exception if test file is not valid
 */
class TestFileParser{

public:
   TestFileParser(std::string file) : testFile(file){}; // constructor

   void load(); // loads the testFile to the parser
   // TestCase GetTestCase(); // returns the TestCase built from this file

private:
   std::string testFile;
   rapidxml::xml_document<> doc; // file iterator

   int buildTestCase(); // builds the test case
   int getOwnship(rapidxml::xml_node<> *node); // handles parsing data for ownship
   int getMovement(rapidxml::xml_node<> *node); // handles parsing data for movement
   bool isAttribute(rapidxml::xml_node<> *node, std::string attribute); // validates that attribute exists
   int getSensors(rapidxml::xml_node<> *node); // handles parsing sensors
   int getPlanes(rapidxml::xml_node<> *node); // handles parsing data for other planes
   bool isCoordinate(rapidxml::xml_node<> *node); // validates that all xyz coordinates exists
};

#endif //SAA_APPLICATION_TESTFILEPARSER_H
