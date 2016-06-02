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
