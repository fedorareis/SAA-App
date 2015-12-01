//
// Created by Kyle Piddington on 11/24/15.
//

#include "ConnectionInfo.h"

ConnectionInfo::ConnectionInfo(int port):
   host("NO_HOST"),
   port(port),
   is_client(false)
{ }
ConnectionInfo::ConnectionInfo(std::string host, int port):
      host(host),
      port(port),
      is_client(true)
{

}

