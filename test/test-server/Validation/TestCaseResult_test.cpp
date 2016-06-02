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

TEST(ResultPlane, loadFromProtobuf)
{
   Vector * pos = new Vector();
   pos->set_x(1);
   pos->set_y(2);
   pos->set_z(3);
   Vector * vel = new Vector();
   vel->set_x(-1);
   vel->set_y(-2);
   vel->set_z(-3);
   CDTIPlane cdtiPlane;
   cdtiPlane.set_allocated_position(pos);
   cdtiPlane.set_allocated_velocity(vel);
   cdtiPlane.set_id("N12345");
   cdtiPlane.set_severity(CDTIPlane_Severity::CDTIPlane_Severity_TRAFFIC);
   ResultPlane plane = ResultPlane::fromGoogleProtobuf(cdtiPlane);
   ASSERT_DOUBLE_EQ(1,plane.getPosition().x);
   ASSERT_DOUBLE_EQ(2,plane.getPosition().y);
   ASSERT_DOUBLE_EQ(3,plane.getPosition().z);
   ASSERT_DOUBLE_EQ(-1,plane.getVelocity().x);
   ASSERT_DOUBLE_EQ(-2,plane.getVelocity().y);
   ASSERT_DOUBLE_EQ(-3,plane.getVelocity().z);
   ASSERT_EQ("N12345", plane.getTag());
   ASSERT_EQ(CDTIPlane_Severity_TRAFFIC, plane.getSeverity());

}