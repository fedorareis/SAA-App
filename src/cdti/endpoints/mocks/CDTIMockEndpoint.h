//
// Created by Kyle Piddington on 11/30/15.
//

#ifndef SAA_APPLICATION_CDTIMOCKENDPOINT_H
#define SAA_APPLICATION_CDTIMOCKENDPOINT_H
#include "cdti/endpoints/CDTIEndpoint.h"
#include "common/protobuf/cdti.pb.h"
class CDTIMockEndpoint : public CDTIEndpoint
{
private:
    CDTIReport* report;
    int time = 0;
public:
   CDTIMockEndpoint();
   const CDTIEndpoint& operator >> (::google::protobuf::Message & msg) const;
    bool isRunning() const;
    void step();

};
#endif //SAA_APPLICATION_CDTIMOCKENDPOINT_H
