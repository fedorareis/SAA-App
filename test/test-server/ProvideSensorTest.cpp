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
// Created by Kyle Piddington on 1/19/16.
//

/** Small test to check that GoogleMock is working*/
#include <gtest/gtest.h>
#include <test-server/TestServer.h>
#include <test-server/TestEnvironment.h>
#include "mocks/SensorEndpoint_test.h"
using ::testing::_;
/*
 * @TODO: Mock ServerSocket, SensorEndpoint->getSocket
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
*/