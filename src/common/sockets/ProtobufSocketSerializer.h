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
#ifndef __PROTOBUF_SOCKET_SERIALIZER_H__
#define __PROTOBUF_SOCKET_SERIALIZER_H__
#include <google/protobuf/message.h>

/**
 * The protocl buffer socket serializer is used to encode header data
 * into any protocal buffer. The data contains the length of the buffer.
 */
class ProtobufSocketSerializer
{
public:
   /**
    * Serialize data for sending over a socket
    * @param  msg    the protcol buffer message
    * @param  packet The data buffer to write data into. This will be allocated in the serializer
    * @return        the number of bytes encoded.
    */
   static int serialize(const ::google::protobuf::Message & msg, char * &packet);
};
#endif