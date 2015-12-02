//
// Created by Kyle Piddington on 11/15/15.
//

#include <iostream>
#include "SaaApplication.h"
#include "Correlation.h"
#include "Decision.h"

ServerSocket * SaaApplication::cdtiSocket = nullptr;

void acceptNetworkConnection(ServerSocket *acceptingSocket, ServerSocket *bindingSocket)
{

   bindingSocket->accept(*acceptingSocket);
   std::cout << "Server has accepted cdti socket" << std::endl;

}

void SaaApplication::report()
{
   setupSockets(4000);
   std::thread t1(acceptNetworkConnection,&this->cdtiOut, getCdtiSocket());
   //std::thread t2(acceptNetworkConnection,&this->validationOut, getCdtiSocket());
   t1.join();
   //t2.join();
   std::cout << "Hello from Saa App!" << std::endl;
   Correlation cor;
   Decision dec;
   cor.report();
   dec.report(&list);
   auto rep = dec.generateReport(&list);
   cdtiOut << (*rep);
   delete rep;
}

ServerSocket *SaaApplication::getCdtiSocket() {
   return cdtiSocket;
}

void SaaApplication::setupSockets(int cdtiPort) {
   cdtiSocket = new ServerSocket(cdtiPort);
}
