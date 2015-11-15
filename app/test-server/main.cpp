/**
 * Entry point of the test-server application
 */
#include "test-server/TestServer.h"
int main(int argC, const char* argV[])
{
   TestServer server;
   server.report();

   return 0;
}