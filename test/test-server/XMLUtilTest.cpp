//
// Created by Kyle Piddington on 5/10/16.
// Updated by Helen Hwang on 5/27/16
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <../lib/xml-parser/rapidxml.hpp>
#include <test-server/XMLUtil.h>
#include <stdexcept>

using ::testing::_;
TEST(TestXMLUtil,TestFloatExtraction)
{

    rapidxml::xml_attribute<> attrib;
    attrib.value("1.0");
    double extractedVal  = XMLUtil::ExtractFloat(&attrib);
    EXPECT_FLOAT_EQ(extractedVal, 1.0);
    attrib.value("-5.3");
    extractedVal  = XMLUtil::ExtractFloat(&attrib);
    EXPECT_FLOAT_EQ(extractedVal, -5.30);
    try
    {
        attrib.value("blah");
        extractedVal  = XMLUtil::ExtractFloat(&attrib);
        FAIL();
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }

}

TEST(TestXMLUtil, TestBoolExtraction)
{
    rapidxml::xml_attribute<> attrib;
    attrib.value("false");
    bool extractedVal = XMLUtil::ExtractBool(&attrib);
    EXPECT_FALSE(extractedVal);
    attrib.value("true");
    extractedVal = XMLUtil::ExtractBool(&attrib);
    EXPECT_TRUE(extractedVal);
    attrib.value("True");
    extractedVal = XMLUtil::ExtractBool(&attrib);
    EXPECT_TRUE(extractedVal);

}