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
#include <test-server/Validation/Validator.h>
#include <test-server/Validation/ValidationWriter.h>

TestEnvironment::TestEnvironment() {

}

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
   //std::cout << "Server is accepting adsb socket on " << TestServer::getAdsbSocket()->getSocket().getPort() << std::endl;
   //std::cout << "Server is accepting ownship socket on " << TestServer::getOwnshipSocket()->getSocket().getPort() << std::endl;
   std::thread t1(acceptNetworkConnection,&this->adsbSensor,TestServer::getAdsbSocket());
   std::thread t2(acceptNetworkConnection,&this->ownshipSensor,TestServer::getOwnshipSocket());
   t1.join();
   t2.join();

   this->cdtiSocket = std::shared_ptr<ClientSocket>(new ClientSocket());


   std::cout << "Connecting to client on 6000..." << std::endl;
   try {
      this->ownshipSensor.getEndpoint().getSocket().connectToClient((*cdtiSocket), 6000);
      std::cout << "Successfully connected to client" << std::endl;
   }
   catch(SocketException exc)
   {
      std::cout << exc.description() << std::endl;

   }


}

void TestEnvironment::start(TestCase & tc)
{
   bool sendADSB = tc.getOwnship().getADSBEnabled();
   Validator validator(tc, this->cdtiSocket);
   try{
      while(tc.isRunning())
      {

         ownshipSensor.sendData(tc.getOwnship());
         if(sendADSB)
         {

            for(auto plane = tc.getPlanes().begin(); plane != tc.getPlanes().end(); plane++)
            {
               adsbSensor.sendData(*plane);
            }
         }
         tc.update(1);
         sleep(1); //sleep for one second before sending next data batch.
      }
   }
   catch(SocketException exc)
   {
      std::cout << "Socket exception: " << exc.description() << std::endl;
   }
   validator.endSimulation();

   ValidationWriter::writeErrors(std::cout, validator);

}
