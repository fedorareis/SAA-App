//Taken from tldp.org/LDP/LG/issue74/misc/tougher
#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"
#include <google/protobuf/message.h>
#include <thread>


/**
 * A Server Socket is a socket used primarely by a server application,
 * or whenever the socket expects to recieve a connection, instead of
 * connect to one.
 * 
 * String data and Protobuf data can be sent over the sockets.
 */
class ServerSocket : private Socket
{
 public:
   /**
    * Create and open a socket on the specified port
    */
   ServerSocket (const int port );
   /**
    * create a socket for accepting a current connection
    */
   ServerSocket(){}

   /**
    * Close the socket
    */
   virtual ~ServerSocket();

   /**
   * Write a string to the client
   * String  std::string the string to write
   */
   virtual const ServerSocket& operator << ( const std::string& ) const;
   /**
    * Read a string form the client
    * string    std::string    the string to read into
    */
   virtual const ServerSocket& operator >> ( std::string& ) const;
   /**
    * Write a protocl buffer to the client
    * msg    protobufMessage   The message to write
    */
   virtual const ServerSocket& operator << ( const ::google::protobuf::Message & msg ) const;
   /**
    * Read a protocol buffer from the client into message
    * msg    protobufMessage   the message to read into
    */
   virtual const ServerSocket& operator >> ( ::google::protobuf::Message & msg ) const;

   /**
    * Accept a connection, and bind it to the new socket
    */
   virtual void accept ( ServerSocket& );

   void close(){ Socket::close();}

   int getPort();

   private:
   /**
    * Read a the header length from a protocol buffer
    * @param  data The raw bytes of the protocl buffer
    * @return      the length of the header
    */
   ::google::protobuf::uint32 read_protobuf_header(const char * data) const;
   /**
    * Read a protocol buffer from raw data
    * @param msg  the message to read
    * @param data the raw data containing the message, plust the header
    */
   void read_protobuf(::google::protobuf::Message & msg, const char * data) const;

};


#endif