//
// Created by Kyle Piddington on 1/20/16.
//

#ifndef SAA_APPLICATION_SERVERSOCKET_TEST_H
#define SAA_APPLICATION_SERVERSOCKET_TEST_H

#include <gmock/gmock.h>
#include <common/sockets/ClientSocket.h>


class ServerSocket_test : public ServerSocket {
   public:
   ServerSocket_test(){}
   ~ServerSocket_test(){}

   MOCK_CONST_METHOD0(WRITE,  void());
   virtual const ServerSocket& operator << ( const ::google::protobuf::Message & msg ) const
   {
       WRITE();
       return *this;
   };

   /**
    * Recieve protcol buffer data from the host
    * @param msg the message to read into
    * @return the socket, for chaining.
    */
   MOCK_CONST_METHOD0(READ, ::google::protobuf::Message * ());
   virtual const ServerSocket& operator >> ( ::google::protobuf::Message & msg ) const
   {
       msg.CopyFrom(*READ());
       return *this;
   };

   MOCK_CONST_METHOD0(hasData,bool());
};


#endif //SAA_APPLICATION_SERVERSOCKET_TEST_H_H
