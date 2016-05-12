//
// Created by Kyle Piddington on 5/10/16.
//

#ifndef SAA_APPLICATION_XMLUTIL_H
#define SAA_APPLICATION_XMLUTIL_H

#include <../lib/xml-parser/rapidxml.hpp>

/**
 * RapidXML extraction functions
 */
namespace XMLUtil {
   /**
    * Extract a floating point value from an xml attribute.
    */
    double ExtractFloat(rapidxml::xml_attribute<> * attribute);
   /**
    * Extract a boolean from an xml attribute.
    */
    bool  ExtractBool(rapidxml::xml_attribute<> * attribute);
};


#endif //SAA_APPLICATION_XMLUTIL_H
