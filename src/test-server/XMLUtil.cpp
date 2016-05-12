//
// Created by Kyle Piddington on 5/10/16.
//

#include "XMLUtil.h"
#include <string>
#include <cstring>
/**
    * Extract a floating point value from an xml attribute.
    */
double XMLUtil::ExtractFloat(rapidxml::xml_attribute<> * attribute)
{
    return std::atof(attribute->value());
}
/**
 * Extract a boolean from an xml attribute.
 */
bool  XMLUtil::ExtractBool(rapidxml::xml_attribute<> * attribute)
{
    std::string data(attribute->value());
    return strcmp(data.c_str(), "true") == 0;
}
