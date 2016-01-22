//
// Created by Kyle Piddington on 11/30/15.
//

#ifndef SAA_APPLICATION_CDTISOCKETENDPOINT_H
#define SAA_APPLICATION_CDTISOCKETENDPOINT_H

#include "cdti/endpoints/CDTIEndpoint.h"
#include "common/sockets/ClientSocket.h"
class CDTISocketEndpoint : public CDTIEndpoint
{
private:
    ClientSocket socket;
public:
   CDTISocketEndpoint(std::string host, int port);
   const CDTIEndpoint& operator >> (::google::protobuf::Message & msg) const;
    bool isRunning() const;
};


#endif //SAA_APPLICATION_CDTISOCKETENDPOINT_H
