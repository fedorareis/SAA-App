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
//Basic Client socket
#ifndef ClientSocket_class
#define ClientSocket_class

#include <google/protobuf/message.h>
#include "Socket.h"


/**
 * A Client Socket is a socket that connects to an open port.
 * The client socket should be used when it wants to communicate
 * with an already open socket.
 *
 * String data and Protocol buffer data can be sent through the socket
 */
class ClientSocket : private Socket
{
public:
   /**
    * Create a new socket, and connect to the specified host and port
    * @param host  the name of the host computer
    * @param port  the port to connect to.
    */
   ClientSocket ( std::string host, int port );

   ClientSocket ( const sockaddr_in host );

   ClientSocket(const ClientSocket & other);

   ClientSocket();
   /**
    * Close the socket
    */
   virtual ~ClientSocket(){};

   virtual void connect(std::string host, int port);
   virtual void connect(const sockaddr_in host);

   /**
    * Send string data to the ost
    * @param string the data to send
    * @return the socket, for chaining
    */


   virtual const ClientSocket& operator << ( const std::string& ) const;
   /**
    * Recieve string data from the host
    * @param string the string to read data into
    * @return the socket, for chaining
    */
   virtual const ClientSocket& operator >> ( std::string& ) const;
   /**
    * Send protocol buffer data from the host
    * @param msg the message to send
    * @return the Socket, for chaining
    */
   virtual const ClientSocket& operator << ( const ::google::protobuf::Message & msg ) const;
   /**
    * Recieve protcol buffer data from the host
    * @param msg the message to read into
    * @return the socket, for chaining.
    */
   virtual const ClientSocket& operator >> ( ::google::protobuf::Message & msg ) const;

   virtual bool hasData() const;

   virtual void close()
   {
      Socket::close();
   }
private:
   /**
    * Read the length of the protocol buffer, from the header
    * @param  header raw data conatining the protocol buffer header
    * @return        the length of the protobuffer message
    */
   ::google::protobuf::uint32 read_protobuf_header(const char* header) const;
   /**
    * Read a protocal buffer from raw data.
    * @param msg  the message to read into
    * @param data the raw data
    */
   void read_protobuf(::google::protobuf::Message & msg, const char * data) const;


};


#endif
