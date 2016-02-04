//
// Created by Kyle Piddington on 11/15/15.
//

#ifndef SAA_APPLICATION_TESTSERVER_H
#define SAA_APPLICATION_TESTSERVER_H

#include <common/sockets/ServerSocket.h>
#include <test-server/endpoints/SensorEndpoint.h>

class TestServer{
public:
   static void provideOwnshipEndpoint(SensorEndpoint * endpoint);
   static void provideAdsbEndpoint(SensorEndpoint * endpoint);
   static void provideTcasEndpoint(SensorEndpoint * endpoint);
    static void provideRadarEndpoint(SensorEndpoint * endpoint);

   static void shutdown();
   void report();

   static SensorEndpoint * getOwnshipSocket();
   static SensorEndpoint * getAdsbSocket();
   static SensorEndpoint * getTcasSocket();
   static SensorEndpoint * getRadarSocket();

private:
   static SensorEndpoint * ownshipSocket;
   static SensorEndpoint * adsbSocket;
   static SensorEndpoint * tcasSocket;
   static SensorEndpoint * radarSocket;

};
#endif //SAA_APPLICATION_TESTSERVER_H
