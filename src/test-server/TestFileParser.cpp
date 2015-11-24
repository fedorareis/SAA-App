//
// Created by Helen Hwang on 11/18/15.
//
#include <sstream>
#include "TestFileParser.h"

using namespace rapidxml;
/**
 * This initializes the parser
 */
void TestFileParser::load() {
   // loading document
   std::ifstream file(testFile);
   if (!file) std::cerr << "Could not open the file '"<<testFile<<"'!" << std::endl;
   else {
      std::stringstream buffer;
      buffer << file.rdbuf();
      file.close();
      std::string content(buffer.str());
      doc.parse<0>(&content[0]);

      // reads the document
      try {

         buildTestCase();
      }
      catch(std::exception& e)
      {
         std::cout << e.what() << std::endl;
      }

      std::cout<<"=================================================================\n";
   }
}

/**
 * Reads the test case information
 */
void TestFileParser::buildTestCase()
{
   std::cout<<"------------------------------------------------------"<<std::endl;
   xml_node<> *node = doc.first_node("test");
   std::cout<<"Test name: "<<node->first_attribute("name")->value()<<std::endl;
   std::cout<<"Description: "<<node->first_attribute("description")->value()<<std::endl;
   std::cout<<"------------------------------------------------------"<<std::endl;

   xml_node<> *inside = node->first_node("ownship");

   // parsing ownship data
   getOwnship(inside);

   inside = node->first_node("plane");

   // parse planes
   getPlanes(inside);
}

/**
 * Reading ownship data
 */
void TestFileParser::getOwnship(xml_node<> *node)
{
   xml_node<> *ownship = node;
   std::cout<<"[Ownship] "<<ownship->first_attribute("tag")->value()<<std::endl;

   //parses sensor data
   getSensors(ownship);

   // parse movement
   getMovement(ownship->first_node("movement"));
}

/**
 * Parses the sensor data
 */
void TestFileParser::getSensors(xml_node<> *node)
{
   int count = 0;
   std::cout<<"[sensor(s)]"<<std::endl;
   // checking whether tcas exists
   {
      xml_node<> *sensor = node->first_node("tcas");
      if (sensor) {
         if (isAttribute(sensor, "enabled")) {
            std::cout << "   Tcas = " << sensor->first_attribute("enabled")->value() << std::endl;
         }
         if (isAttribute(sensor, "error")) {
            std::cout << "      error = " << sensor->first_attribute("error")->value() << std::endl;
         }
         count++;
      }
   }

   // checking whether radar exists
   {
      xml_node<> *sensor = node->first_node("radar");
      if (sensor) {
         if (isAttribute(sensor, "enabled")) {
            std::cout << "   Radar = " << sensor->first_attribute("enabled")->value()<<std::endl;
         }
         if (isAttribute(sensor, "error")) {
            std::cout << "      error = " << sensor->first_attribute("error")->value() << std::endl;
         }
      }
      count++;
   }

   // checking whether ads-b exists
   {
      xml_node<> *sensor = node->first_node("ads-b");
      if (sensor) {
         if (isAttribute(sensor, "enabled")) {
            std::cout << "   ADS-B = " << sensor->first_attribute("enabled")->value()<<std::endl;
         }
         if (isAttribute(sensor, "error")) {
            std::cout << "      error = " << sensor->first_attribute("error")->value() << std::endl;
         }
      }
      count++;
   }

   // there was no sensor
   if(count == 0)
   {
      std::cerr<<"There is no sensor for this plane";
   }
}

/**
 * Checks whether the attribute exists or not
 */
bool TestFileParser::isAttribute(xml_node<> *node, std::string att)
{
      if(node->first_attribute(att.c_str()))
      {
         return true;
      }
   return false;
}

/**
 * Checks whether all xyz value for coordinate exists
 */
bool TestFileParser::isCoordinate(xml_node<> *node)
{
   if(!isAttribute(node, "x") || !isAttribute(node, "y") || !isAttribute(node,"z"))
   {
      return false;
   }
   return true;
}

/**
 * Parses the movements
 */
void TestFileParser::getMovement(rapidxml::xml_node<> *node)
{
   xml_node<> *movement = node;
   // Checks that the movment type is defined
   if(movement->first_attribute("type")) {
      std::cout << "[Movement] " << movement->first_attribute("type")->value() << std::endl;
   }

   // maybe validate movements...
   movement = movement->first_node("position");
   if(isCoordinate(movement)) {
      std::cout << "   Position = (" << movement->first_attribute("x")->value() << ", ";
      std::cout << movement->first_attribute("y")->value() << ", ";
      std::cout << movement->first_attribute("z")->value() << ")" << std::endl;
   }

   movement = movement->next_sibling("direction");
   if(isCoordinate(movement)) {
      std::cout << "   Direction = (" << movement->first_attribute("x")->value() << ", ";
      std::cout << movement->first_attribute("y")->value() << ", ";
      std::cout << movement->first_attribute("z")->value() << ")" << std::endl;
   }
}

/**
 * Iterates all the intruder planes
 */
void TestFileParser::getPlanes(rapidxml::xml_node<> *node)
{
   // Iterate over planes
   for ( xml_node<> *plane = node ; plane; plane = plane->next_sibling())
   {
      std::cout<<"\n[Plane] "<<plane->first_attribute("tag")->value()<<std::endl;

      // gets the sensor data
      getSensors(plane);

      // parse movement
      getMovement(plane->first_node("movement"));
   }
}