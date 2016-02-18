//
// Created by Kyle Piddington on 1/20/16.
//

#include <gtest/gtest.h>
#include <mocks/SensorEndpoint_test.h>
#include <test-server/planes/LinearMotion.h>
#include <test-server/TestCase.h>
#include <test-server/Validation/Validator.h>
#include "mocks/ClientSocket_test.h"
#include "test-server/Validation/ValidationWriter.h"
using ::testing::Return;
TEST(ValidationWriter, successfulTest)
{
   std::stringstream ss;
   //Mock
   std::shared_ptr<ClientSocket_test> testSocket(new ClientSocket_test());
   EXPECT_CALL(*testSocket, hasData())
         .WillOnce(Return(true))
         .WillOnce(Return(false))
         .RetiresOnSaturation();

   CDTIReport report;
   report.set_timestamp(0);
   //Mock

   EXPECT_CALL(*testSocket,READ())
         .WillOnce(Return(&report));


   SensorEndpoint_test test;
   TestCase tc;
   TestServerPlane plane;
   plane.setMotion(LinearMotion(Vector3d(0,0,0),Vector3d(1,1,1)));
   tc.setOwnship(plane);

   Validator validator(tc,testSocket);
   validator.endSimulation();
   EXPECT_FALSE(validator.hasErrors());
   ValidationWriter::writeErrors(ss,validator);
   EXPECT_STREQ("Correlation is perfect, no errors detected!\n",ss.str().c_str());
}
TEST(ValidationWriter, failedTest)
{
   std::stringstream ss;
   //Mock
   CDTIReport report;
   report.add_planes();

   report.set_timestamp(0);
   //Mock
   std::shared_ptr<ClientSocket_test> testSocket(new ClientSocket_test());
   EXPECT_CALL(*testSocket, hasData())
         .WillOnce(Return(true))
         .WillOnce(Return(false))
         .RetiresOnSaturation();

   EXPECT_CALL(*testSocket,READ())
         .WillOnce(Return(&report));

   SensorEndpoint_test test;
   TestCase tc;
   TestServerPlane plane;
   plane.setMotion(LinearMotion(Vector3d(0,0,0),Vector3d(1,1,1)));
   tc.setOwnship(plane);
   tc.addPlane(plane);
   tc.addPlane(plane);

   Validator validator(tc,testSocket);
   validator.endSimulation();


}