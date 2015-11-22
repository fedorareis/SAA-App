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

   // Note: find a better way to include resource folder....
   std::cout<<"\nTest File 1"<<std::endl;
   std::string s("/Users/Helen/Desktop/REPO/saa-application/resources/testCases/TestCaseExample.xml");
   TestFileParser parser(s);
   parser.load();

   std::cout<<"\nTest File 2"<<std::endl;
   std::string s1("/Users/Helen/Desktop/REPO/saa-application/resources/testCases/TestCaseExample2.xml");
   TestFileParser parser_1(s1);
   parser_1.load();
   return 0;
}