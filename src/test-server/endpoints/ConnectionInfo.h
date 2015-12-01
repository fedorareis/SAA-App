//
// Created by Kyle Piddington on 11/24/15.
//

#ifndef SAA_APPLICATION_CONNECTIONINFO_H
#define SAA_APPLICATION_CONNECTIONINFO_H
#include <string>


struct ConnectionInfo {
   public:
      ConnectionInfo(int port);
      ConnectionInfo(std::string host, int port);
      const std::string host;
      const int port;
      const bool is_client;


};


#endif //SAA_APPLICATION_CONNECTIONINFO_H
