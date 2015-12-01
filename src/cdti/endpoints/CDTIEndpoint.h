//
// Created by Kyle Piddington on 11/30/15.
//

#ifndef SAA_APPLICATION_CDTIENDPOINT_H
#define SAA_APPLICATION_CDTIENDPOINT_H
#include <google/protobuf/Message.h>

class CDTIEndpoint {
   public:
   virtual const CDTIEndpoint& operator >> (::google::protobuf::Message & msg) const = 0;

};


#endif //SAA_APPLICATION_CDTIENDPOINT_H
