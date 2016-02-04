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


   TestServer::provideRadarEndpoint(new SocketSensorEndpoint(5003));
   TestServer::provideTcasEndpoint(new SocketSensorEndpoint(5002));
   TestServer::provideAdsbEndpoint(new SocketSensorEndpoint(5001));
   TestServer::provideOwnshipEndpoint(new SocketSensorEndpoint(5000));

   std::cout<<"\n----Test File 1----"<<std::endl;
   //__DIR__ is injected in compile time
   std::string s(__DIR__"/resources/TestCaseExample2Planes.xml");
   TestFileParser parser;
   // true if building test case is successful
   if(parser.load(s))
   {
      TestCase testCase = parser.GetTestCase();

      TestEnvironment environment;
      environment.acceptConnections();
      environment.start(testCase);

      std::cout << "Environment has finished accepting connections" << std::endl;
   }
   TestServer::shutdown();
/*
   std::cout<<"\n----Test File 2----"<<std::endl;
   //__DIR__ is injected in compile time
   std::string s2(__DIR__"/resources/TestCaseExample2.xml");
   // true if building test case is successful
   if(parser.load(s2)) {
      TestCase tc = parser.GetTestCase();

   }

   std::cout<<"\n-----Test File 3----"<<std::endl;
   //__DIR__ is injected in compile time
   std::string s3(__DIR__"/resources/TestCaseExample3.xml");
   // true if building test case is successful
   if(parser.load(s3)) {
      TestCase tc = parser.GetTestCase();

      }
   }
*/

/*
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

   testCase.setTotalTime(10.0f);
   //Test cases start at lat 0 long 0
   testCase.complete();


   TestEnvironment environment;
   environment.acceptConnections();
   environment.start(testCase);

   std::cout << "Environment has finished accepting connections" << std::endl;
   TestServer::shutdown();
*/
   return 0;
}