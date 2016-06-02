/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
//
// Created by Helen Hwang on 11/18/15.
//

#ifndef SAA_APPLICATION_TESTFILEPARSER_H
#define SAA_APPLICATION_TESTFILEPARSER_H

#include <iostream>
#include <fstream>
#include <exception>
#include <../lib/xml-parser/rapidxml.hpp>
#include "TestCase.h"
#include "planes/Motion.h"

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
   timeMissingErr, // = 16 total time for test to run is missing
   testMissingError, // =17 test tag is missing on the test
   inputFormatError // =18 input data type is wrong
};

/**
 * This class parses the XML file that contains one test case and validates
 * whether the file contains all necessary the configuration data.
 *
 * Throws Exception if test file is not valid
 */
class TestFileParser{

public:
   TestFileParser(){}; // constructor; if ever changed to Singleton pattern, move to private
   TestFileParser& instance(){static TestFileParser parser; return parser;}; // For Singleton pattern
   bool load(std::string testFile); // loads the testFile to the parser
   TestCase GetTestCase(); // returns the TestCase built from this file

private:
   rapidxml::xml_document<> doc; // file iterator
   TestCase test; // test case for this testFile
   static TestFileParser *parser; // for Singleton pattern

   int buildTestCase(); // builds the test case
   int getOwnship(rapidxml::xml_node<> *node); // handles parsing data for ownship
   int getMovement(rapidxml::xml_node<> *node, TestServerPlane & plane); // handles parsing data for movement
   bool isAttribute(rapidxml::xml_node<> *node, std::string attribute); // validates that attribute exists
   int getSensors(rapidxml::xml_node<> *node, TestServerPlane & plane); // handles parsing sensors
   int getPlanes(rapidxml::xml_node<> *node); // handles parsing data for other planes
   bool isCoordinate(rapidxml::xml_node<> *node); // validates that all xyz coordinates exists
};

#endif //SAA_APPLICATION_TESTFILEPARSER_H
