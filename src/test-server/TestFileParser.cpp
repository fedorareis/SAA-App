//
// Created by Helen Hwang on 11/18/15.
//
#include "TestFileParser.h"
#include <xml-parser/rapidxml.hpp>

/**
 * This initializes the parser
 */
void TestFileParser::load()
{
   std::cout<<"test file is "<<TestFileParser::testFile<<std::endl;
   // try using the xml parser
   using namespace rapidxml;

   /* //xml document is loaded through a string variable before you can work with
      // loading document
      xml_document<> doc;
      std::ifstream file("xml_file.xml");
      std::stringstream buffer;
      buffer << file.rdbuf();
      file.close();
      std::string content(buffer.str());
      doc.parse<0>(&content[0]);*/

   /* File == One test case */


}

void TestFileParser::buildTestCase()
{
   // builds the test case
   /**
    * // Getting the root node
     xml_node<> *pRoot = doc.first_node(); // With the xml example above this is the <document/> node
    */

   // Iterating through the child node
   /*
    * for(xml_node<> *pNode=pRoot->first_node("node"); pNode; pNode=pNode->next_sibling())
{
// This loop will walk you through two nodes:
node attribute="0" and then node attribute="1"
// Do something here
}
    */
}

/**
 * Returns true if required configuration data is all found
 */
bool TestFileParser::getOwnship()
{
   //

   // Getting to the first node by its name
   /* xml_attribute<> *pAttr = pNode->first_attribute("attribute"); */


   // Getting the attribute
   /* xml_node<> *pNode = pRoot->first_node("node"); */

   // Getting to the first node without caring for its name
   /* pRoot->first_node(); */

   // Getting string value
   /* std::string strValue = pAttr->value();*/

   // Getting int value
   /* int nValue = atoi(pAttr->value()); */
}

/**
 * Returns true if required configuration data is all found
 * Requires at least 1 plane to be present
 */
bool TestFileParser::getPlanes()
{
   //
}
