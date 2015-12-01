//
// Created by Kyle Piddington on 11/30/15.
//

#include "CDTIMockEndpoint.h"
CDTIMockEndpoint::CDTIMockEndpoint() {
   //Initialize report
}
const CDTIEndpoint& CDTIMockEndpoint::operator >> (::google::protobuf::Message & msg) const
{
   msg.CopyFrom(report);
   return *this;
}
