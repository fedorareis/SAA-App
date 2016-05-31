//
// Created by Kyle Piddington on 5/10/16.
// Updated by Helen Hwang on 5/27/16
//

#include "XMLUtil.h"
#include <string>
#include <cstring>
#include <typeinfo>
#include <iostream>
#include <sstream>

/**
    * Extract a floating point value from an xml attribute.
    */
double XMLUtil::ExtractFloat(rapidxml::xml_attribute<> * attribute)
{
    // Run-time check to determine whether b is actually a Derived*
    float value;
    std::istringstream iss(attribute->value());
    iss >> value;
    if(iss.bad() || iss.fail())
    {
        throw std::exception();
    }
    return value;
}
/**
 * Extract a boolean from an xml attribute.
 */
bool  XMLUtil::ExtractBool(rapidxml::xml_attribute<> * attribute)
{
    std::string data(attribute->value());
    return strcmp(data.c_str(), "true") == 0;
}
