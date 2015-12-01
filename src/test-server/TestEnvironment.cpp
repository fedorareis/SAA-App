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

   bindingSocket->accept(acceptingSocket->getEndpoint().getSocket());
   std::cout << "Server has accepted adsb socket" << std::endl;

}

bool TestEnvironment::acceptConnections()
{
   //Threaded accept
   std::cout << "Server is accepting adsb socket on " << TestServer::getAdsbSocket()->getPort() << std::endl;
   std::cout << "Server is accepting ownship socket on " << TestServer::getOwnshipSocket()->getPort() << std::endl;
   std::thread t1(acceptNetworkConnection,&this->adsbSensor,TestServer::getAdsbSocket());
   std::thread t2(acceptNetworkConnection,&this->ownshipSensor,TestServer::getOwnshipSocket());
   t1.join();
   t2.join();



   std::cout << "Server would send stuff here!";
}
