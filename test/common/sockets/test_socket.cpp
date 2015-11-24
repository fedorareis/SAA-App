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