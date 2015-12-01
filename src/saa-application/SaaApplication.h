//
// Created by Kyle Piddington on 11/15/15.
//

#ifndef SAA_APPLICATION_SAAAPPLICATION_H
#define SAA_APPLICATION_SAAAPPLICATION_H

#include <vector>
#include <common/protobuf/cdti.pb.h>

class SaaApplication
{
public:
   void report();
private:
   std::vector<CDTIPlane *> list;
};
#endif //SAA_APPLICATION_SAAAPPLICATION_H
