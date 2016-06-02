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
#ifndef __CONNECTION_MANAGER_H__
#define __CONNECTION_MANAGER_H__

#include <common/sockets/ServerSocket.h>
#include <google/protobuf/message.h>
#include <mutex>

/**
 * ServerConnectionmanager provides a convinent way
 * for the SAA application to asynchronously accept
 */
class ServerConnectionManager
{
public:
   /**
    * Create the connection manager
    * @param acceptingSocket the binding socket.
    */

   ~ServerConnectionManager();
   void init(std::shared_ptr<ServerSocket> acceptingSocket);
   /**
    * Accept will block until a connection occurs, or acceptingSocket is closed.
    * @throws SocketException if a connection error occurs.
    */
   void accept();
   /**
    * Monitor creates a new thread, and will passivly accept connections until shutdown
    * is called.
    */
   void monitor();

   /**
    * Shutdown closes all open connections, and the original socket.
    */
   void shutdown();

   /**
    * Send a message to all currently connected clients.
    * @param msg [description]
    */
   void sendMessage(google::protobuf::Message & msg);

   void addClient(std::shared_ptr<ServerSocket> shared_ptr);

   bool getIsMonitoring();

   std::shared_ptr<ServerSocket> getBindingSocket();

   private:

   bool isMonitoring;
   std::mutex connectionManagerMutex;
   std::vector<std::shared_ptr<ServerSocket>> acceptedSockets;
   std::shared_ptr<ServerSocket> bindingSocket;
   std::thread monitorThread;
};
#endif