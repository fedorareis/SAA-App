//
// Created by Kyle Piddington on 5/10/16.
//

#include "XMLUtil.h"
#include <string>
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
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    return std::strcmp(data.c_str(), "true") == 0;
}