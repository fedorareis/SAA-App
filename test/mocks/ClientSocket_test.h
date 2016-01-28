//
// Created by Kyle Piddington on 1/20/16.
//

#ifndef SAA_APPLICATION_CLIENTSOCKET_TEST_H
#define SAA_APPLICATION_CLIENTSOCKET_TEST_H

#include <gmock/gmock.h>
#include <common/sockets/ClientSocket.h>


class ClientSocket_test : public ClientSocket {
   public:
   ClientSocket_test(){}
   ~ClientSocket_test(){}

   MOCK_CONST_METHOD0(WRITE,  void());
   virtual const ClientSocket& operator << ( const ::google::protobuf::Message & msg ) const
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
   virtual const ClientSocket& operator >> ( ::google::protobuf::Message & msg ) const
   {
      msg.CopyFrom(*READ());
      return *this;
   };

   MOCK_CONST_METHOD0(hasData,bool());
};


#endif //SAA_APPLICATION_CLIENTSOCKET_TEST_H
