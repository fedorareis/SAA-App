#ifndef SAA_APPLICATION_ALERTMESSAGES_CDTI_H
#define SAA_APPLICATION_ALERTMESSAGES_CDTI_H

#include <common/sockets/ClientSocket.h>
#include <common/protobuf/cdti.pb.h>
#include <cdti/endpoints/CDTISocketEndpoint.h>
#include <thread>

class AlertMessages
{
private:
    CDTIEndpoint& cdtiSocket;
    CDTIReport report;
public:
    AlertMessages(CDTIEndpoint& socket);
    CDTIReport getMessage();
    CDTIEndpoint* getSocket(){return &cdtiSocket;};
};
#endif //SAA_APPLICATION_ALERTMESSAGES_CDTI_H