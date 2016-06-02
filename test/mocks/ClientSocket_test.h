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
