//
// Created by Helen Hwang on 11/18/15.
//
#include <sstream>
#include <test-server/planes/LinearMotion.h>
#include "TestFileParser.h"

using namespace rapidxml;

/**
 * This initializes the parser and checks that the file can be open
 */
bool TestFileParser::load(std::string testFile) {
   // loading document
   std::ifstream file(testFile);

   // Checks that file is loaded
   if (!file) {
      std::cout << "Error in opening the file '"<<testFile<<"'!" << std::endl;
      return false;
   } else {
      std::stringstream buffer;
      buffer << file.rdbuf();
      file.close();
      std::string content(buffer.str());
      doc.parse<0>(&content[0]);

      auto code = buildTestCase();

      // reads the document
      if(code)
      {
         // in the future, create message to pass onto exception and throw that exception
         std::cout<<"Aborting building test case due to ";
         switch(code) {
            case 1:
            std::cout<<"ownship missing its tag"<<std::endl;
               break;
            case 2:
            std::cout<<"ownship missing all the sensors"<<std::endl;
               break;
            case 3:
            std::cout<<"ownship missing its direction"<< std::endl;
               break;
            case 4:
            std::cout<<"ownship missing its position"<<std::endl;
               break;
            case 5:
            std::cout<<"the test missing its ownship data"<<std::endl;
               break;
            case 6:
            std::cout<<"one of the planes missing its tag"<<std::endl;
               break;
            case 7:
            std::cout<<"one of the planes missing all the sensors"<<std::endl;
               break;
            case 8:
            std::cout<<"one of the planes missing its direction"<< std::endl;
               break;
            case 9:
            std::cout<<"one of the planes missing its position"<<std::endl;
               break;
            case 16:
            std::cout<<"the document not starting with 'test'tag"<<std::endl;
               break;
            default:
               std::cout << "error" << std::endl;
         }
         return false;
      } else return true;
   }
}

/**
 * Reads the test case information
 */
int TestFileParser::buildTestCase()
{
   xml_node<> *node = doc.first_node("test");

   // test must exist
   if(node) {

      // Name and description are optional
      if (isAttribute(node, "name")) {
         test.setName(node->first_attribute("name")->value());
         // std::cout << "Test name: " << node->first_attribute("name")->value() << std::endl;
      }
      if (isAttribute(node, "description")) {
         // std::cout << "Description: " << node->first_attribute("description")->value() << std::endl;
      }

      // Total time is required
      if(isAttribute(node, "time")) {
         double time = std::atof(node->first_attribute("time")->value());
         test.setTotalTime(time);
         //std::cout<<"Total time to run the test: "<< time <<std::endl;
      } else return ErrorCode::timeMissingErr;

      // Ownship is necessary
      xml_node<> *inside = node->first_node("ownship");

      // parsing ownship data
      auto code = getOwnship(inside);
      // error in ownship data
      if (code) {
         return code;
      }

      // Planes are optionals
      inside = node->first_node("plane");

      // parse planes
      code = getPlanes(inside);
      // error in intruder data
      if (code) {
         return code;
      }
      return ErrorCode::success;
   }

   return ErrorCode::testMissingError;
}

/**
 * Reads and initializes ownship data
 */
int TestFileParser::getOwnship(xml_node<> *node)
{
   TestServerPlane plane;

   // checks that ownship data exists
   if(node) {
      xml_node<> *ownship = node;
      // checks that tag is included
      if (isAttribute(ownship, "tag")) {
         plane.setTailNumber(ownship->first_attribute("tag")->value());
      } else return ErrorCode::os_tagErr;

      //parses sensor data
      auto code = getSensors(ownship, &plane);
      // checks the sensor for ownship
      if (code) {
         return ErrorCode::os_sensorErr;
      }

      // parse movement
      code = getMovement(ownship->first_node("movement"), &plane);
      // checks the movement for ownship
      if (code) {
         if(code == ErrorCode::positionError)
            return ErrorCode::os_posErr;
         else
            return ErrorCode::os_mvntErr;
      }

      // successfully added ownship data to the test case
      test.setOwnship(plane);

      return ErrorCode::success;
   }

   return ErrorCode::os_missingErr;
}

/**
 * Parses the sensor data; There has to be at least 1 sensor for any plane
 */
int TestFileParser::getSensors(xml_node<> *node, TestServerPlane* aircraft)
{
   TestServerPlane *plane = aircraft;
   int count = 0;
   std::cout<<"     sensor(s)"<<std::endl;

   // checking whether tcas exists
   {
      xml_node<> *sensor = node->first_node("tcas");
      // checks that sensor exists
      if (sensor) {

         // checks if there is enabled tag
         if (isAttribute(sensor, "enabled")) {
            if(!std::strcmp(sensor->first_attribute("enabled")->value(),"true")) {
               std::cout<<"    tcas enabled"<<std::endl;
               (*plane).setTcasEnabled(true);
            }
            else {
               std::cout<<"    tcas diabled"<<std::endl;
               (*plane).setTcasEnabled(false);
            }
         }
         // checks if error value is specified
         if (isAttribute(sensor, "error")) {
            std::cout << "    tcas error = " << sensor->first_attribute("error")->value() << std::endl;
         }
         count++;
      }
   }

   // checking whether radar exists
   {
      xml_node<> *sensor = node->first_node("radar");
      // checks that sensor exists
      if (sensor) {
         // checks if there is enabled tag
         if (isAttribute(sensor, "enabled")) {
            std::cout << "   Radar = " << sensor->first_attribute("enabled")->value()<<std::endl;
         }
         // checks if error value is specified
         if (isAttribute(sensor, "error")) {
            std::cout << "      radar error = " << sensor->first_attribute("error")->value() << std::endl;
         }
         count++;
      }
   }

   // checking whether ads-b exists
   {
      xml_node<> *sensor = node->first_node("ads-b");
      // checks that sensor exists
      if (sensor) {
         // checks if there is enabled tag
         if (isAttribute(sensor, "enabled")) {
            // string to bool conversion
            if(!std::strcmp(sensor->first_attribute("enabled")->value(), "true"))
            { std::cout<<"    ads-b enabled"<<std::endl;
               (*plane).setAdsbEnabled(true);
            } else {
               std::cout<<"    ads-b disabled"<<std::endl;
               (*plane).setAdsbEnabled(false);
            }
         }
         // checks if error value is specified
         if (isAttribute(sensor, "error")) {
            std::cout << "    ads-b error = " << sensor->first_attribute("error")->value() << std::endl;
         }
         count++;
      }
   }

   // there was no sensor for this plane
   if(!count)
   {
      return ErrorCode::sensorError;
   }
   return ErrorCode::success;
}

/**
 * Checks whether the attribute exists or not
 * precondition: node is not null
 */
bool TestFileParser::isAttribute(xml_node<> *node, std::string att)
{
   // checks whether attribute exists
   if(node->first_attribute(att.c_str()))
   {
      return true;
   }

   return false;
}

/**
 * Checks whether all xyz value for coordinate exists
 * precondition: node is not null
 */
bool TestFileParser::isCoordinate(xml_node<> *node)
{
   // all xyz has to be present in order to be considered coordinate
   if (!isAttribute(node, "x") || !isAttribute(node, "y") || !isAttribute(node, "z")) {
      return false;
   }
   return true;
}

/**
 * Parses the movements
 */
int TestFileParser::getMovement(rapidxml::xml_node<> *node, TestServerPlane *aircraft) {
   xml_node<> *movement = node;

   TestServerPlane *plane = aircraft;
   std::string type;

   // checks that movement exists
   if (movement) {
      // Checks that the movment type is defined
      if (movement->first_attribute("type")) {
         type = movement->first_attribute("type")->value();
      }
      else return ErrorCode::missingTypeErr;

      // Working around vector and Motion stuff; Will change later
      double pos_x;
      double pos_y;
      double pos_z;
      double dir_x;
      double dir_y;
      double dir_z;

      // checks movements
      {
         xml_node<> *pos = movement->first_node("position");
         // position must exist
         if(pos) {
            // coordinate must exist
            if (isCoordinate(pos)) {
               // working around
               pos_x = std::atof(pos->first_attribute("x")->value());
               pos_y = std::atof(pos->first_attribute("y")->value());
               pos_z = std::atof(pos->first_attribute("z")->value());
            }
            else return ErrorCode::coordMissingErr;
         }
         else return ErrorCode::positionError;
      }

      // checks direction
      {
         xml_node<> *dir = movement->first_node("direction");
         // direction must exist
         if(dir)
         {
            // coordinate must exist
            if (isCoordinate(dir)) {
               // working around
               dir_x = std::atof(dir->first_attribute("x")->value());
               dir_y = std::atof(dir->first_attribute("y")->value());
               dir_z = std::atof(dir->first_attribute("z")->value());
            }
            else return ErrorCode::coordMissingErr;
         }
         else return ErrorCode::directionError;
      }

      // motion type
      if(type == "linear")
      {
         std::cout<<"    Motion is Linear"<<std::endl;
         (*plane).setMotion(LinearMotion(Vector3d(pos_x,pos_y,pos_z), Vector3d(dir_x,dir_y,dir_z)));
      }

      return ErrorCode::success;
   }

   return ErrorCode::movementError;
}

/**
 * Iterates all the intruder planes
 */
int TestFileParser::getPlanes(xml_node<> *node)
{
   // Iterate over all planes except ownship
   for (xml_node<> *plane = node ; plane; plane = plane->next_sibling())
   {
      TestServerPlane intruder;

      // tag is necessary
      if(isAttribute(plane, "tag")) {
         intruder.setTailNumber(plane->first_attribute("tag")->value());
      } else return ErrorCode::p_tagErr;

      // gets the sensor data
      auto code = getSensors(plane, &intruder);
      if(code)
      {
         return ErrorCode::p_sensorErr;
      }

      // parse movement
      xml_node<> *movement = plane->first_node("movement");
      // movement must exist
      if(movement) {
         code = getMovement(movement, &intruder);
         if (code) {
            if (code == ErrorCode::positionError) return ErrorCode::p_posErr;
            else return ErrorCode::p_mvntErr;
         }
      }

      // successfully add intruder to the test case
      test.addPlane(intruder);
   }
   return ErrorCode::success;
}

TestCase TestFileParser::GetTestCase()
{
   return test;
}