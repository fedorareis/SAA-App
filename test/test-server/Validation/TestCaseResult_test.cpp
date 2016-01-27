//
// Created by Kyle Piddington on 1/20/16.
//

#include <gtest/gtest.h>
#include <common/protobuf/cdti.pb.h>
#include <test-server/Validation/TestCaseResult.h>
#include <test-server/Validation/TestCaseResult.h>

TEST(TestCaseResult, loadFromEmptyProtobuf)
{
   CDTIReport report;
   report.set_timestamp(1.0);
   TestCaseResult result = TestCaseResult::fromGoogleProtobuf(report);
   ASSERT_EQ(0, result.getPlanes().size());
}
TEST(TestCaseResult, loadFromProtobuf)
{
   CDTIReport report;
   report.set_timestamp(1.0);
   report.add_planes();
   report.add_planes();
   TestCaseResult result = TestCaseResult::fromGoogleProtobuf(report);
   ASSERT_EQ(2, result.getPlanes().size());
}

TEST(TestCaseResult, loadTimeFromProtobuf)
{
   CDTIReport report;
   report.set_timestamp(5.0);
   TestCaseResult result = TestCaseResult::fromGoogleProtobuf(report);
   ASSERT_EQ(5.0, result.getTime());
}
