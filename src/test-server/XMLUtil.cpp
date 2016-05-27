//
// Created by Kyle Piddington on 5/10/16.
// Updated by Helen Hwang on 5/27/16
//

#include "XMLUtil.h"
#include <string>
#include <cstring>
#include <typeinfo>
#include <iostream>

/**
    * Extract a floating point value from an xml attribute.
    */
double XMLUtil::ExtractFloat(rapidxml::xml_attribute<> * attribute)
{
    // Run-time check to determine whether b is actually a Derived*
    float val = static_cast<float>(std::atof(attribute->value()));

    // If b was originally a Derived*, then d3 is a valid pointer.
    if(val)
    {
        return val;
    }
    else
    {
        // Run-time check failed.
        throw std::exception();
    }
}
/**
 * Extract a boolean from an xml attribute.
 */
bool  XMLUtil::ExtractBool(rapidxml::xml_attribute<> * attribute)
{
    std::string data(attribute->value());
    return strcmp(data.c_str(), "true") == 0;
}
