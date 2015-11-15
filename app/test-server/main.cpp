/**
 * Entry point of the test-server application
 */
#include <common/Common.h>
#include "test-server/TestServer.h"
int main(int argC, const char* argV[])
{
   TestServer server;
   server.report();
   Common common;
   common.report();


   return 0;
}