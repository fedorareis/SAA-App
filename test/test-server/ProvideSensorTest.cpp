//
// Created by Kyle Piddington on 1/19/16.
//

/** Small test to check that GoogleMock is working*/
#include <gtest/gtest.h>
#include <test-server/TestServer.h>
#include <test-server/TestEnvironment.h>
#include "mocks/SensorEndpoint_test.h"
using ::testing::_;
TEST(ProvideTrest, testMocks)
{
   SensorEndpoint_test * endpoint1 = new SensorEndpoint_test();
   SensorEndpoint_test * endpoint2 = new SensorEndpoint_test();
   EXPECT_CALL(*endpoint1,accept(_)).Times(1);
   EXPECT_CALL(*endpoint2,accept(_)).Times(1);

   TestServer server;
   server.provideAdsbEndpoint(endpoint1);
   server.provideOwnshipEndpoint(endpoint2);
   TestEnvironment env;
   env.acceptConnections();


}