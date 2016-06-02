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