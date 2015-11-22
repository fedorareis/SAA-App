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
   std::cout<<"\nLoading testFile:"<<std::endl;

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
      buildTestCase();
   }
}

/**
 * Reads the test case information
 */
void TestFileParser::buildTestCase()
{
   std::cout<<"------------------------------------------------------"<<std::endl;
   xml_node<> *node = doc.first_node("test");
   xml_node<> *inside = node->first_node("name");
   std::cout<<"Test name: "<<inside->value()<<std::endl;
   inside = node->first_node("description");
   std::cout<<"Description: "<<inside->value()<<std::endl;
   std::cout<<"------------------------------------------------------"<<std::endl;

   inside = node->first_node("ownship");
   // parsing ownship data
   getOwnship(inside);
}

void TestFileParser::getOwnship(xml_node<> *inside)
{
   std::cout<<"[Ownship]"<<std::endl;
   xml_node<> *ownship = inside;
   ownship = ownship->first_node("tag");
   std::cout<<"Tag: "<<ownship->value()<< std::endl;

}
