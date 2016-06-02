/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#include <common/sockets/SocketException.h>
#include "ServerConnectionManager.h"
#include <iostream>

void handleMonitor(ServerConnectionManager * mntr)
{
   while(mntr->getIsMonitoring())
   {
      try{
         std::shared_ptr<ServerSocket> newSock = std::make_shared<ServerSocket>();
         mntr->getBindingSocket()->accept(*newSock);
         mntr->addClient(newSock);
      }
      catch(SocketException exc)
      {
         std::cout << "Socket exception in monitor loop" << std::endl;
      }

   }
 
}

/**
 * Accept a new connection.
 * This call blocks!
 */
void ServerConnectionManager::accept() {
   std::shared_ptr<ServerSocket> newSock = std::make_shared<ServerSocket>();
   this->getBindingSocket()->accept(*newSock);
   this->addClient(newSock);
}

void ServerConnectionManager::init(std::shared_ptr<ServerSocket> acceptingSocket) {
   this->bindingSocket = acceptingSocket;
}

void ServerConnectionManager::monitor() {
   if(!isMonitoring)
   {
      isMonitoring = true;
      monitorThread = std::thread(handleMonitor,this);
   }
}


void ServerConnectionManager::shutdown() {
   if(isMonitoring)
   {
      /**
       * Change to close, connect to self, and then close the accepting socket.
       */
      isMonitoring = false;
      ClientSocket dummy;
      dummy.connect("localhost",bindingSocket->getPort());
      monitorThread.join();
   }

   acceptedSockets.clear();
   //Socket destructors take care of everything else.
}

void ServerConnectionManager::sendMessage(google::protobuf::Message &msg) {
   std::lock_guard<std::mutex>(this->connectionManagerMutex);
   std::vector<std::vector<std::shared_ptr<ServerSocket>>::iterator> removeList;
   for(auto sock = acceptedSockets.begin();
       sock != acceptedSockets.end(); ++sock) {
      try {
         if ((*sock) != nullptr)
         {
            google::protobuf::Message * uniqueMsg;
            uniqueMsg = msg.New();
            uniqueMsg->CopyFrom(msg);
//            std::cout << uniqueMsg->DebugString() << std::endl;
            *(*sock) << *uniqueMsg;
            delete uniqueMsg;
         }
      }
      catch (SocketException exc) {

         removeList.push_back(sock);
      }
   }
   for(auto rm : removeList)
   {
      acceptedSockets.erase(rm);
   }

}

/**
 * Add a client to the
 */
void ServerConnectionManager::addClient(std::shared_ptr<ServerSocket> sock) {
   std::lock_guard<std::mutex>(this->connectionManagerMutex);
   this->acceptedSockets.push_back(sock);
}

bool ServerConnectionManager::getIsMonitoring() {
   return this->isMonitoring;
}

std::shared_ptr<ServerSocket> ServerConnectionManager::getBindingSocket() {
   return this->bindingSocket;
}

ServerConnectionManager::~ServerConnectionManager() {
   //shutdown();
}
