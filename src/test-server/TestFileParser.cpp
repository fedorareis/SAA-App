//
// Created by Helen Hwang on 11/18/15.
//
#include <sstream>
#include "TestFileParser.h"

using namespace rapidxml;

/**
 * This initializes the parser and checks that the file can be open
 */
void TestFileParser::load(std::string testFile) {
   // loading document
   std::ifstream file(testFile);

   // Checks that file is loaded
   if (!file) std::cerr << "Error in opening the file '"<<testFile<<"'!" << std::endl;
   else {
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
         std::cerr<<"Aborting building test case due to ";
         switch(code) {
            case 1:
            std::cerr<<"ownship missing its tag"<<std::endl;
               break;
            case 2:
            std::cerr<<"ownship missing all the sensors"<<std::endl;
               break;
            case 3:
            std::cerr<<"ownship missing its direction"<< std::endl;
               break;
            case 4:
            std::cerr<<"ownship missing its position"<<std::endl;
               break;
            case 5:
            std::cerr<<"the test missing its ownship data"<<std::endl;
               break;
            case 6:
            std::cerr<<"one of the planes missing its tag"<<std::endl;
               break;
            case 7:
            std::cerr<<"one of the planes missing all the sensors"<<std::endl;
               break;
            case 8:
            std::cerr<<"one of the planes missing its direction"<< std::endl;
               break;
            case 9:
            std::cerr<<"one of the planes missing its position"<<std::endl;
               break;
            case 16:
            std::cerr<<"the document not starting with 'test'tag"<<std::endl;
               break;
            default:
               std::cout << "error" << std::endl;
         }
      }
      std::cout<<"=================================================================\n";
   }
}

/**
 * Reads the test case information
 */
int TestFileParser::buildTestCase()
{
   TestCase test;

   std::cout<<"------------------------------------------------------"<<std::endl;

   xml_node<> *node = doc.first_node("test");

   // test must exist
   if(node) {

      // Name and description are optional
      if (isAttribute(node, "name")) {
         test.setName(node->first_attribute("name")->value());
         std::cout << "Test name: " << node->first_attribute("name")->value() << std::endl;
      }
      if (isAttribute(node, "description")) {
         std::cout << "Description: " << node->first_attribute("description")->value() << std::endl;
      }
      std::cout << "------------------------------------------------------" << std::endl;

      // Ownship is necessary
      xml_node<> *inside = node->first_node("ownship");

      // parsing ownship data
      auto code = getOwnship(inside);
      // error in ownship data
      if (code) {
         return code;
      }

      // Planes are optionals?
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
 * Reading ownship data
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
         std::cout << "[Ownship] " << ownship->first_attribute("tag")->value() << std::endl;
      } else return ErrorCode::os_tagErr;

      //parses sensor data
      auto code = getSensors(ownship, plane);
      // checks the sensor for ownship
      if (code) {
         return ErrorCode::os_sensorErr;
      }

      // parse movement
      code = getMovement(ownship->first_node("movement"), plane);
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
int TestFileParser::getSensors(xml_node<> *node, const TestServerPlane &plane)
{
   int count = 0;
   std::cout<<"[sensor(s)]"<<std::endl;

   // checking whether tcas exists
   {
      xml_node<> *sensor = node->first_node("tcas");
      // checks that sensor exists
      if (sensor) {

         // checks if there is enabled tag
         if (isAttribute(sensor, "enabled")) {
            //plane.setTcasEnabled(sensor->first_attribute("enabled")->value());
            std::cout << "   Tcas = " << sensor->first_attribute("enabled")->value() << std::endl;
         }
         // checks if error value is specified
         if (isAttribute(sensor, "error")) {
            std::cout << "      error = " << sensor->first_attribute("error")->value() << std::endl;
         }
         count++;
      }
      std::cout<<"tcas exist! count ="<<count<<std::endl;
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
            std::cout << "      error = " << sensor->first_attribute("error")->value() << std::endl;
         }
         count++;
         std::cout<<"radar exist! count ="<<count<<std::endl;
      }
   }

   // checking whether ads-b exists
   {
      xml_node<> *sensor = node->first_node("ads-b");
      // checks that sensor exists
      if (sensor) {
         // checks if there is enabled tag
         if (isAttribute(sensor, "enabled")) {
            // plane.setAdsbEnabled(sensor->first_attribute("enabled")->value());
            std::cout << "   ADS-B = " << sensor->first_attribute("enabled")->value()<<std::endl;
         }
         // checks if error value is specified
         if (isAttribute(sensor, "error")) {
            std::cout << "      error = " << sensor->first_attribute("error")->value() << std::endl;
         }
         count++;
         std::cout<<"ads-b exist! count ="<<count<<std::endl;
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
int TestFileParser::getMovement(rapidxml::xml_node<> *node, const TestServerPlane &plane) {
   xml_node<> *movement = node;

   // checks that movement exists
   if (movement) {
      // Checks that the movment type is defined
      if (movement->first_attribute("type")) {
         std::string type = movement->first_attribute("type")->value();
         std::cout << "[Movement] " << type << std::endl;
//         if(type)
      }
      else return ErrorCode::missingTypeErr;

      // checks movements
      {
         xml_node<> *pos = movement->first_node("position");
         // position must exist
         if(pos) {
            // coordinate must exist
            if (isCoordinate(pos)) {
               std::cout << "   Position = (" << pos->first_attribute("x")->value() << ", ";
               std::cout << pos->first_attribute("y")->value() << ", ";
               std::cout << pos->first_attribute("z")->value() << ")" << std::endl;
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
               std::cout << "   Direction = (" << dir->first_attribute("x")->value() << ", ";
               std::cout << dir->first_attribute("y")->value() << ", ";
               std::cout << dir->first_attribute("z")->value() << ")" << std::endl;
            }
            else return ErrorCode::coordMissingErr;
         }
         else return ErrorCode::directionError;
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
         std::cout << "\n[Plane] " << plane->first_attribute("tag")->value() << std::endl;
      } else return ErrorCode::p_tagErr;

      // gets the sensor data
      auto code = getSensors(plane, intruder);
      if(code)
      {
         return ErrorCode::p_sensorErr;
      }

      // parse movement
      xml_node<> *movement = plane->first_node("movement");
      // movement must exist
      if(movement) {
         code = getMovement(movement, intruder);
         if (code) {
            if (code == ErrorCode::positionError) return ErrorCode::p_posErr;
            else return ErrorCode::p_mvntErr;
         }
      }
   }
   return ErrorCode::success;
}