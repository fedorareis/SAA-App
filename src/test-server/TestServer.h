//
// Created by Kyle Piddington on 11/15/15.
//

#ifndef SAA_APPLICATION_TESTSERVER_H
#define SAA_APPLICATION_TESTSERVER_H

#include <common/sockets/ServerSocket.h>

class TestServer{
   public:
   static void setupSockets(int ownshipPort, int adsbPort, int tcasPort, int radarPort);
   static void shutdown();
   void report();

   static ServerSocket * getOwnshipSocket();
   static ServerSocket * getAdsbSocket();
   static ServerSocket * getTcasSocket();
   static ServerSocket * getRadarSocket();
   private:
   static ServerSocket * ownshipSocket;
   static ServerSocket * adsbSocket;
   static ServerSocket * tcasSocket;
   static ServerSocket * radarSocket;

};
#endif //SAA_APPLICATION_TESTSERVER_H
