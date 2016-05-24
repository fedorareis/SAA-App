//
// Created by Kyle Piddington on 11/24/15.
//

#include "TestEnvironment.h"
#include "TestServer.h"
#include <common/sockets/SocketException.h>
#include <test-server/Validation/Validator.h>
#include <test-server/Validation/ValidationWriter.h>

TestEnvironment::TestEnvironment():
   delay(true)
{

}

void acceptNetworkConnection(std::shared_ptr<Sensor> acceptingSocket, SensorEndpoint * bindingEndpoint)
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
   createSensors();
   //Threaded accept
   //std::cout << "Server is accepting adsb socket on " << TestServer::getAdsbSocket()->getSocket().getPort() << std::endl;
   //std::cout << "Server is accepting ownship socket on " << TestServer::getOwnshipSocket()->getSocket().getPort() << std::endl;



   std::cout << "Connecting to client on 6000..." << std::endl;
   try {

      this->ownshipSensor->getEndpoint().getSocket().connectToClient((*cdtiSocket), 6000);
      std::cout << "Successfully connected to client" << std::endl;
   }
   catch(SocketException exc)
   {
      std::cout << exc.description() << std::endl;
   }


}
void printProgressBar(TestCase & tc)
{
   int barWidth = 70;
   float progress = (float)tc.getElapsedTime()/tc.getTotalTime();
   std::cout << "[";
   int pos = barWidth * progress;
   for (int i = 0; i < barWidth; ++i) {
      if (i < pos) std::cout << "=";
      else if (i == pos) std::cout << ">";
      else std::cout << " ";
   }
   std::cout << "] " << int(progress * 100.0) << " %\r";
   std::cout.flush();
}

void TestEnvironment::start(TestCase & tc)
{

   bool sendADSB = tc.getOwnship().getADSBEnabled();
   bool sendRadar = tc.getOwnship().getRadarEnabled();
   bool sendTcas = tc.getOwnship().getTcasEnabled();
   if(tc.getNoiseEnabled())
   {
      adsbSensor->setJitter(true);
      radarSensor->setJitter(true);
      tcasSensor->setJitter(true);
   }
   std::shared_ptr<Validator> validator = nullptr;
   if(this->cdtiSocket != nullptr)
   {
      validator = std::make_shared<Validator>(tc, this->cdtiSocket);

   }
   try{
      while(tc.isRunning()) {
         tc.update(1);
         ownshipSensor->sendData(tc.getOwnship(), tc.getOwnship());

         for (auto plane = tc.getPlanes().begin(); plane != tc.getPlanes().end(); plane++) {
            if (sendADSB && plane->getADSBEnabled())
            {
               adsbSensor->sendData(*plane, tc.getOwnship());
            }
            if (plane->getTcasEnabled() && sendTcas)
            {
               tcasSensor->sendData(*plane, tc.getOwnship());
            }
            if (sendRadar)
            {
               radarSensor->sendData(*plane, tc.getOwnship());
            }

         }
         printProgressBar(tc);
         if(this->delay)
         {
             sleep(1); //sleep for one second before sending next data batch.
         }

      }
      adsbSensor->close();
      ownshipSensor->close();
      tcasSensor->close();
      radarSensor->close();
   }
   catch(SocketException exc)
   {
      std::cout << "Socket exception: " << exc.description() << std::endl;
   }
   if(validator != nullptr)
   {
      validator->endSimulation();
      ValidationWriter::writeErrors(std::cout, *validator);

   }


}



void TestEnvironment::createSensors() {
   adsbSensor = std::make_shared<AdsbSensor>(new SocketSensorEndpoint());
   ownshipSensor = std::make_shared<OwnshipSensor>(new SocketSensorEndpoint());
   tcasSensor = std::make_shared<TcasSensor>(new SocketSensorEndpoint());
   radarSensor =  std::make_shared<RadarSensor>(new SocketSensorEndpoint());
   this->cdtiSocket = std::shared_ptr<ClientSocket>(new ClientSocket());

   std::thread t1(acceptNetworkConnection,this->adsbSensor,TestServer::getAdsbSocket());
   std::thread t2(acceptNetworkConnection,this->ownshipSensor,TestServer::getOwnshipSocket());
   std::thread t3(acceptNetworkConnection,this->tcasSensor,TestServer::getTcasSocket());
   std::thread t4(acceptNetworkConnection,this->radarSensor,TestServer::getRadarSocket());
   t1.join();
   t2.join();
   t3.join();
   t4.join();



}
