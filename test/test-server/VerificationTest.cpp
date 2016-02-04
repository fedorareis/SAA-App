//
// Created by lejonmcgowan on 1/26/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <common/protobuf/cdti.pb.h>
#include <test-server/Validation/TestCaseResult.h>
#include <test-server/TestCase.h>
#include <test-server/Validation/VerificationTest.h>

#include <mocks/VerificationTest_test.h>

using ::testing::_;
TEST(TestVerifier,testMock)
{
    TestCase testCase1, testCase2, testCase3;

    VerificationTest* verificationTest = new VerificationTest_test(std::make_shared<TestCase>(testCase1));
    //EXPECT_CALL(*verificationTest,verify(_)).WillOnce(::testing::Return(true));
    CDTIReport report;
    TestCaseResult testCaseResult = TestCaseResult::fromGoogleProtobuf(report);
    bool result = verificationTest->verify(testCaseResult);
    ASSERT_TRUE(result);
}