/**
 * Entry point of the test-server application
 */
#include <common/Common.h>
#include <iosfwd>
#include <string>
#include <test-server/TestEnvironment.h>
#include <test-server/Validation/PositionVerificationTest.h>
#include <test-server/Validation/NumPlanesVerificationTest.h>
#include <test-server/Validation/Validator.h>
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

   //__DIR__ is injected in compile time
   std::string test;
   if(argC < 2)
   {
      std::cout << "test-server: <test-file-name.xml>" << std::endl;
      return -1;
   }

   else
   {
      test = std::string(argV[1]);
   }
   std::string s(test);
   TestFileParser parser;
   // true if building test case is successful
   try {


      if (parser.load(s)) {
         std::cout << s << std::endl;

         TestCase testCase = parser.GetTestCase();
         PositionVerificationTest positionTest(std::make_shared<TestCase>(TestCase(testCase)));
         NumPlanesVerificationTest numPlanesTest(std::make_shared<TestCase>(TestCase(testCase)));
         //Validator::addTester(std::make_shared<PositionVerificationTest>(std::move(positionTest)));
         Validator::addTester(std::make_shared<NumPlanesVerificationTest>(std::move(numPlanesTest)));
         TestEnvironment environment;
         environment.acceptConnections();
         environment.start(testCase);

         std::cout << "Environment has finished accepting connections" << std::endl;
      }
      TestServer::shutdown();
   }
   catch(std::exception e)
   {
      std::cerr << "Error in loading test case: " << e.what() << std::endl;
   }

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