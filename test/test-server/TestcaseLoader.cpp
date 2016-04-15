//
// Created by Kyle Piddington on 1/19/16.
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