//
// Created by Kyle Piddington on 11/30/15.
//

#include "CDTISocketEndpoint.h"

CDTISocketEndpoint::CDTISocketEndpoint(std::string host, int port):
socket(host,port)
{

}
const CDTIEndpoint& CDTISocketEndpoint::operator >> (::google::protobuf::Message & msg) const
{
   socket >> msg;
   return *this;
}
