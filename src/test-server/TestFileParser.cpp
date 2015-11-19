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
   xml_document<> doc; // root of the DOM hierarchy; xml_node and a memory_pool
   //doc.parse<0>(text); // 0 means default parse flags; flags must be a compile-time constant!

   /* File == One test case */

   // to access DOM tree, use methods of xml_node and xml_attribute classes
   /**
    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
    xml_node<> *node = doc.first_node("foobar");
    cout << "Node foobar has value " << node->value() << "\n";
    for (xml_attribute<> *attr = node->first_attribute();
           attr; attr = attr->next_attribute())
    {
       cout << "Node foobar has attribute " << attr->name() << " ";
       cout << "with value " << attr->value() << "\n";
    }
    */
}


