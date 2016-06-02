/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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
