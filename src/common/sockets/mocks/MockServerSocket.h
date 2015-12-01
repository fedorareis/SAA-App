//
// Created by Kyle Piddington on 11/30/15.
//

#ifndef SAA_APPLICATION_MOCKSERVERSOCKET_H
#define SAA_APPLICATION_MOCKSERVERSOCKET_H

#include <common/sockets/ServerSocket.h>
#include <common/sockets/SocketException.h>
#include <string>
class MockServerSocket : public ServerSocket
{
   public:

   MockServerSocket():
         ServerSocket()
   {

   }
   ~MockServerSocket()
   {

   }
   virtual const ServerSocket& operator << ( const std::string& ) const
   {
      return *this;
   }

   /**
    * Read a string form the client
    * string    std::string    the string to read into
    */
   virtual const ServerSocket& operator >> ( std::string& ) const
   {
      throw SocketException("Trying to read from a mock server socket!");
   }
   /**
    * Write a protocl buffer to the client
    * msg    protobufMessage   The message to write
    */
   virtual const MockServerSocket& operator << ( const ::google::protobuf::Message & msg ) const
   {
      return *this;
   }
   /**
    * Read a protocol buffer from the client into message
    * msg    protobufMessage   the message to read into
    */
   virtual const MockServerSocket& operator >> ( ::google::protobuf::Message & msg ) const
   {
      throw SocketException("Trying to read from a mock server socket!");

   }


   /**
    * Accept a connection, and bind it to the new socket
    */
   virtual void accept ( ServerSocket& other )
   {
      throw SocketException("Trying to accept on a mock server socket!");
   }

   virtual void close(){

   }

   int getPort(){return -1;}

   virtual void connectToClient(ClientSocket & socket, int port) {
      throw SocketException("Trying to connect on a mock server socket!");
   }


};
#endif //SAA_APPLICATION_MOCKSERVERSOCKET_H
