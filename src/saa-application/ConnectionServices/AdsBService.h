//
// Created by Kyle Piddington on 11/22/15.
//

#ifndef SAA_APPLICATION_ADSBSERVICE_H
#define SAA_APPLICATION_ADSBSERVICE_H
#include "common/protobuf/adsb.pb.h"
#include "common/ConnectionServices/ConnectionInfo"
class AdsBService {
   virtual void init(const ConnectionInfo & info ) = 0;
   virtual void sendData(AdsBReport report) = 0;

};


#endif //SAA_APPLICATION_CDTISERVICE_H
