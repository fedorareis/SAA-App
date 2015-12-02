/**
 * Entry point of the test-server application
 */
#include <common/Common.h>
#include <iosfwd>
#include <string>
#include <test-server/TestEnvironment.h>
#include <test-server/endpoints/mocks/MockSensorEndpoint.h>
#include "test-server/TestServer.h"
#include "test-server/TestFileParser.h"
int main(int argC, const char* argV[])
{

   Common common;
   common.report();
   TestServer::provideAdsbEndpoint(new SocketSensorEndpoint(5000));
   TestServer::provideOwnshipEndpoint(new SocketSensorEndpoint(6000));



   // Note: find a better way to include resource folder....

   std::cout<<"\nTest File 1"<<std::endl;
   //__DIR__ is injected in compile time
   std::string s(__DIR__"/resources/TestCaseExample.xml");
   TestFileParser parser;
   parser.load(s);

   /*
   // contains multiple planes
   std::cout<<"\nTest File 2"<<std::endl;
   std::string s1("/Users/Helen/Desktop/REPO/saa-application/resources/testCases/TestCaseExample2.xml");
   TestFileParser parser_1(s1);
   parser_1.load();

   // contains configuration error
   std::cout<<"\nTest File 3"<<std::endl;
   std::string s2("/Users/Helen/Desktop/REPO/saa-application/resources/testCases/TestCaseExample3.xml");
   TestFileParser parser_2(s2);
   parser_2.load();
    */

   /*
   TestCase testCase;

   TestEnvironment environment(testCase);
   environment.acceptConnections();
   std::cout << "Environment has finished accepting connections" << std::endl;
   TestServer::shutdown();
    */
   return 0;
}