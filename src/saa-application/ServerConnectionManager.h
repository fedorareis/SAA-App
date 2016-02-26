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