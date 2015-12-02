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

   ClientSocket();
   /**
    * Close the socket
    */
   virtual ~ClientSocket(){};

   void connect(std::string host, int port);
   void connect(const sockaddr_in host);

   /**
    * Send string data to the ost
    * @param string the data to send
    * @return the socket, for chaining
    */


   const ClientSocket& operator << ( const std::string& ) const;
   /**
    * Recieve string data from the host
    * @param string the string to read data into
    * @return the socket, for chaining
    */
   const ClientSocket& operator >> ( std::string& ) const;
   /**
    * Send protocol buffer data from the host
    * @param msg the message to send
    * @return the Socket, for chaining
    */
   const ClientSocket& operator << ( const ::google::protobuf::Message & msg ) const;
   /**
    * Recieve protcol buffer data from the host
    * @param msg the message to read into
    * @return the socket, for chaining.
    */
   const ClientSocket& operator >> ( ::google::protobuf::Message & msg ) const;

   bool hasData();

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
