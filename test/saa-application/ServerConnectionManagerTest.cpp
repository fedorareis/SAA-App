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
// Created by Kyle Piddington on 2/17/16.
//
#include <gtest/gtest.h>
#include <common/protobuf/cdti.pb.h>
#include <common/sockets/ServerSocket.h>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include <saa-application/ServerConnectionManager.h>

void check_vector(Vector v, Vector templ)
{
   EXPECT_EQ(v.x(),templ.x());
   EXPECT_EQ(v.y(),templ.y());
   EXPECT_EQ(v.z(),templ.z());

}

TEST(ServerConnectionTest,testMonitorThread)
{
   std::shared_ptr<ServerSocket> socket = std::make_shared<ServerSocket>(1234);
   ServerConnectionManager mgr;
   mgr.init(socket);
   mgr.monitor();
   //Clients need to wait until monitor is set up.
   sleep(1);
   ClientSocket client1, client2, client3;
   try {
      client1.connect("localhost",1234);
      client2.connect("localhost",1234);
      client3.connect("localhost",1234);
   }
   catch(SocketException exc)
   {
      /**
       * Client should connect ok.
       */
      ASSERT_TRUE(false);
   }
   sleep(3); //Wait for server to accept connections
   //Send a message to all clients. Test message is a vector
   Vector vec;
   vec.set_x(1);
   vec.set_y(2);
   vec.set_z(3);
   mgr.sendMessage(vec);
   //Check that all three clients recieved it

   Vector v1, v2, v3;
   client1.operator>>(v1);
   client2.operator>>(v2);
   client3.operator>>(v3);
   check_vector(v1,vec);
   check_vector(v2,vec);
   check_vector(v3,vec);
   //Close one client
   client1.close();
   Vector vec2;
   vec2.set_x(4);
   vec2.set_y(5);
   vec2.set_z(6);
   mgr.sendMessage(vec2);
   client2 >> v2;
   client3 >> v3;
   check_vector(v2,vec2);
   check_vector(v3,vec2);
   mgr.shutdown();

   //Close all clients
}


