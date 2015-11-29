//
// Created by Kyle Piddington on 11/24/15.
//

#include "TestEnvironment.h"
#include "saa-application/ConnectionServices/AdsBService.h"
#include "TestServer.h"
#include <thread>
#include <test-server/endpoints/Sensor.h>
#include <iostream>

TestEnvironment::TestEnvironment(TestCase tc) {
   this->testCase = tc;
}
void acceptNetworkConnection(Sensor * acceptingSocket, ServerSocket * bindingSocket)
{
   std::cout << "Server is accepting adsb socket on " << bindingSocket->getPort() << std::endl;

   bindingSocket->accept(acceptingSocket->getEndpoint().getSocket());
   std::cout << "Server has accepted adsb socket" << std::endl;

}

bool TestEnvironment::acceptConnections()
{
   //Threaded join
   std::thread t1(acceptNetworkConnection,&this->adsbSensor,TestServer::getAdsbSocket());
   t1.join();

   

   std::cout << "Server would send stuff here!";
}
