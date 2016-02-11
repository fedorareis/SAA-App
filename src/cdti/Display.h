//
// Created by lejonmcgowan on 1/21/16.
//

#ifndef SAA_APPLICATION_DISPLAY_H
#define SAA_APPLICATION_DISPLAY_H

#include <common/protobuf/cdti.pb.h>

class Display
{
public:
    virtual void renderReport(CDTIReport& report) = 0;
    virtual void init() = 0;
};
#endif //SAA_APPLICATION_DISPLAY_H
