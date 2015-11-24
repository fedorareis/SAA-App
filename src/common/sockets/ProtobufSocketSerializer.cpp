#include "ProtobufSocketSerializer.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <iostream>
#define HEADER_LEN 4


int ProtobufSocketSerializer::serialize(const ::google::protobuf::Message & msg, char * & packet)
{
   int siz = msg.ByteSize() + HEADER_LEN;//Add four bytes for length
   packet = new char[siz]();

   ::google::protobuf::io::ArrayOutputStream aos(packet,siz);
   ::google::protobuf::io::CodedOutputStream  coded_output(&aos);
   //Write 4 bytes of length information into the output
   coded_output.WriteVarint32(msg.ByteSize());
   msg.SerializeToCodedStream(&coded_output);
   return siz;
}



