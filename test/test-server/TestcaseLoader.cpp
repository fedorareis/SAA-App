//
// Created by Kyle Piddington on 1/19/16.
//
#include <gtest/gtest.h>

#include <test-server/TestCase.h>
#include <test-server/TestFileParser.h>
#include <gmock/gmock.h>

#include "common/Maths.h"


TEST(TestCaseLoader, loadTwoPlanes)
{
   std::string s(__DIR__"/resources/TestCaseTwoPlanes.xml");
   TestFileParser parser;
   // true if building test case is successful
   if(parser.load(s)) {
      TestCase testCase = parser.GetTestCase();
      ASSERT_EQ(2,testCase.getPlanes().size());
   }
   else
   {
      ASSERT_TRUE(false); // Parser could not load test case
   }
}
