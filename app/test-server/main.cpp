/**
 * Entry point of the test-server application
 */
#include <common/Common.h>
#include <iosfwd>
#include <string>
#include <test-server/TestEnvironment.h>
#include <test-server/endpoints/mocks/MockSensorEndpoint.h>
#include <test-server/planes/LinearMotion.h>
#include "test-server/TestServer.h"
#include "test-server/TestFileParser.h"
int main(int argC, const char* argV[])
{

   Common common;
   common.report();
   TestServer::provideAdsbEndpoint(new MockSensorEndpoint());
   TestServer::provideOwnshipEndpoint(new MockSensorEndpoint());



   // Note: find a better way to include resource folder....

   std::cout<<"\nTest File 1"<<std::endl;
   //__DIR__ is injected in compile time
   std::string s(__DIR__"/resources/TestCaseExample.xml");
   TestFileParser parser;
   //parser.load(s);

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


   TestCase testCase;
   TestServerPlane ownshipPlane;
   ownshipPlane.setMotion(LinearMotion(Vector3d(0,0,8000), Vector3d(875,0,0)));
   ownshipPlane.setTailNumber("N00000");
   ownshipPlane.setAdsbEnabled(true);

   TestServerPlane otherPlane;
   otherPlane.setMotion(LinearMotion(Vector3d(5,15,-2000), Vector3d(0,875,0)));
   otherPlane.setTailNumber("N12345");
   otherPlane.setAdsbEnabled(true);

   testCase.setOwnship(ownshipPlane);
   testCase.addPlane(otherPlane);

   testCase.setTotalTime(60.0f);
   //Test cases start at lat 0 long 0
   testCase.complete();


   TestEnvironment environment;
   environment.acceptConnections();
   environment.start(testCase);
   std::cout << "Environment has finished accepting connections" << std::endl;
   TestServer::shutdown();

   return 0;
}