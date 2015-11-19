/**
 * Entry point of the test-server application
 */
#include <common/Common.h>
#include <iosfwd>
#include <string>
#include "test-server/TestServer.h"
#include "test-server/TestFileParser.h"

int main(int argC, const char* argV[])
{
   TestServer server;
   server.report();
   Common common;
   common.report();

   std::string s("TestCaseExample.xml");
   TestFileParser parser(s);
   parser.load();

   return 0;
}