//
// Created by Kyle Piddington on 1/19/16.
// Updated by Helen Hwang on 5/27/16
//
#include <gtest/gtest.h>

#include <test-server/TestCase.h>
#include <test-server/TestFileParser.h>
#include <gmock/gmock.h>

#include "common/Maths.h"

TEST(TestCaseLoader, testFileNotFound)
{
   std::string s(__DIR__"/resources/blahblah.xml");
   TestFileParser parser;

   ASSERT_FALSE(parser.load(s));
}

TEST(TestCaseLoader, testFormatTestNameMissing)
{
   std::string s(__DIR__"/resources/TestFormatMissingName.xml");
   TestFileParser parser;

   ASSERT_FALSE(parser.load(s));
}

TEST(TestCaseLoader, testFormatAllPlanesMissing)
{
   std::string s(__DIR__"/resources/TestAllPlanesMissing.xml");
   TestFileParser parser;

   ASSERT_FALSE(parser.load(s));
}

TEST(TestCaseLoader, testFormatOwnShipMissingAllSensors)
{
   std::string s(__DIR__"/resources/TestOwnshipMissingAllSensors.xml");
   TestFileParser parser;

   ASSERT_FALSE(parser.load(s));
}
TEST(TestCaseLoader, loadBadTestcase)
{
   std::string s(__DIR__"/resources/awesome.png");
   TestFileParser parser;
   ASSERT_ANY_THROW(parser.load(s));
}

TEST(TestCaseLoader, testFormatDataInputFormat)
{
   std::string s(__DIR__"/resources/TestInputFormat.xml");
   TestFileParser parser;

   ASSERT_FALSE(parser.load(s));
}
