#include "ServerSocket.h"
#include "SocketException.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/descriptor.h>
#include <iostream>
#include <thread>
#include "ProtobufSocketSerializer.h"
#define PROTOBUF_HEADER_LEN 4
ServerSocket::ServerSocket(const int port)
{
   //Create the socket
   if(! Socket::create())
   {
      throw SocketException("Could not create server socket.");

   }
   if(! Socket::bind(port))
   {
      throw SocketException("Could not bind to port" + std::to_string(port));

   }
   if(! Socket::listen())
   {
      throw new SocketException("Could not listen on socket");
   }
}

ServerSocket::~ServerSocket()
{

}

//Write S to socket
const ServerSocket & ServerSocket::operator << (const std::string & s) const
{
   if(!Socket::send(s))
   {
      throw SocketException("Could not write to socket");
   }
   return *this;
}
//read data from socket into s
const ServerSocket& ServerSocket::operator >> (std::string & s) const
{
   if(!Socket::recv (s))
   {
      throw SocketException("Could not read from socket");
   }
   return *this;
}

//Taken from http://stackoverflow.com/questions/9496101/protocol-buffer-over-socket-in-c
::google::protobuf::uint32 ServerSocket::read_protobuf_header(const char *  header) const
{
  ::google::protobuf::uint32 size;
  char buf[PROTOBUF_HEADER_LEN];
  memcpy(buf,header,PROTOBUF_HEADER_LEN);
  ::google::protobuf::io::ArrayInputStream ais(buf,PROTOBUF_HEADER_LEN);
  ::google::protobuf::io::CodedInputStream coded_input(&ais);
  coded_input.ReadVarint32(&size);//Decode the header and get the size
  return size;

}
const ServerSocket& ServerSocket::operator << (const ::google::protobuf::Message & msg) const
{
   char * packet;
   int len = ProtobufSocketSerializer::serialize(msg,packet);
   if(!Socket::send(packet, len))
   {
      throw SocketException("Could not write to socket.");
   }
   delete packet;
   return *this;
}

void ServerSocket::read_protobuf(::google::protobuf::Message & msg, const char * data) const
{
   //Read the header again to determine the message length (Could be refactored?)
   ::google::protobuf::uint32 size = read_protobuf_header(data);
   char buf[PROTOBUF_HEADER_LEN + size];
   memcpy(buf,data,PROTOBUF_HEADER_LEN + size);

   ::google::protobuf::io::ArrayInputStream ais(buf,PROTOBUF_HEADER_LEN + size);
   //Re-read the input length
   ::google::protobuf::io::CodedInputStream coded_input(&ais);
   //Read an unsigned integer with Varint encoding, truncating to 32 bits.
   ::google::protobuf::uint32 siz;
   coded_input.ReadVarint32(&siz);
   //read the remainder of the message
   ::google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);
   //De-Serialize
   msg.ParseFromCodedStream(&coded_input);
   //Once the embedded message has been parsed, PopLimit() is called to undo the limit
   coded_input.PopLimit(msgLimit);


}
//read data from socket into s
const ServerSocket& ServerSocket::operator >> (::google::protobuf::Message & msg) const
{
   //Read the first four bytes
   char lenBfr[PROTOBUF_HEADER_LEN];
   if(!Socket::recv(&lenBfr,PROTOBUF_HEADER_LEN,MSG_PEEK))
   {
      throw SocketException("Could not read header from socket");
   }
   ::google::protobuf::uint32 len = read_protobuf_header(lenBfr);
   char dataBuf[len +PROTOBUF_HEADER_LEN];
   if(!Socket::recv (dataBuf, len + PROTOBUF_HEADER_LEN,MSG_WAITALL))
   {
      throw SocketException("Could not read from socket");
   }
   read_protobuf(msg,dataBuf);
   //Parse data and assign to msg
   //
   return *this;
}

void ServerSocket::accept(ServerSocket & sock)
{
   if(!Socket::accept(sock))
   {
      throw SocketException("Could not accept socket");
   }
}


int ServerSocket::getPort() {
   return this->port;
}
