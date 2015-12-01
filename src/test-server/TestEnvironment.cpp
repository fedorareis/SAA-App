//
// Created by Kyle Piddington on 11/24/15.
//

#include "TestEnvironment.h"
#include "saa-application/ConnectionServices/AdsBService.h"
#include "TestServer.h"
#include <thread>
#include <test-server/endpoints/Sensor.h>
#include <iostream>
#include <common/sockets/SocketException.h>

TestEnvironment::TestEnvironment(TestCase tc) {
   this->testCase = tc;

}
//What I raelly want to do is accept a mock service.
void acceptNetworkConnection(Sensor * acceptingSocket, SensorEndpoint * bindingEndpoint)
{

   try{

      bindingEndpoint->accept(acceptingSocket->getEndpoint());
      std::cout << "Server has accepted socket" << std::endl;
   }
   catch(SocketException exc)
   {
      std::cout << exc.description() << std::endl;
   }

}

bool TestEnvironment::acceptConnections()
{
   //Threaded accept
   std::cout << "Server is accepting adsb socket on " << TestServer::getAdsbSocket()->getSocket().getPort() << std::endl;
   std::cout << "Server is accepting ownship socket on " << TestServer::getOwnshipSocket()->getSocket().getPort() << std::endl;
   std::thread t1(acceptNetworkConnection,&this->adsbSensor,TestServer::getAdsbSocket());
   std::thread t2(acceptNetworkConnection,&this->ownshipSensor,TestServer::getOwnshipSocket());
   t1.join();
   t2.join();
   std::cout << "Connecting to client on 4000..." << std::endl;
   try {
      this->ownshipSensor.getEndpoint().getSocket().connectToClient(cdtiSocket, 4000);
   }
   catch(SocketException exc)
   {
      std::cout << exc.description() << std::endl;
   }


   std::cout << "Successfully connected to client" << std::endl;
   std::cout << "Shutting down..." << std::endl;
   std::cout << "Server would send stuff here!";
}
