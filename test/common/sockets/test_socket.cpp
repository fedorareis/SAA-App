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
// Created by Kyle Piddington on 11/23/15.
//

#include "common/sockets/ServerSocket.h"
#include "common/sockets/ClientSocket.h"

#include "catch/catch.hpp"

/* I'm dumb and forgot sockets block, I'll come back to this test later....*/
/*
SCENARIO( "Server socket can be connected to", "[sockets]" ) {
   GIVEN("A valid socket is opened")
   {
      ServerSocket * server;
      REQUIRE_NOTHROW(server = new ServerSocket(30000););
      ServerSocket new_sock;
      REQUIRE_NOTHROW(server->accept(new_sock));

      AND_WHEN("a client connects to the server")
      {
         ClientSocket * cSocket;
         REQUIRE_NOTHROW(cSocket = new ClientSocket("localhost", 30000));

         WHEN("The client sends data to the server")
         {
            *cSocket << "Hello";
            THEN("The server should receive the data")
            {
               std::string data;
               new_sock >> data;
               REQUIRE(data.compare("Hello") == 0);
            }
         }
         delete cSocket;
      }
      delete server;


   }
}
*/