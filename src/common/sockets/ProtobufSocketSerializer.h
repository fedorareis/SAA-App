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