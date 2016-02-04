//
// Created by Kyle Piddington on 1/19/16.
//

#ifndef SAA_APPLICATION_TESTCASERESULT_H
#define SAA_APPLICATION_TESTCASERESULT_H
#include <string>
#include <vector>
#include <common/protobuf/cdti.pb.h>

class ResultPlane
{


};

class TestCaseResult {

   public:
   const std::vector<ResultPlane> & getPlanes(){return planes;}
   static TestCaseResult fromGoogleProtobuf(const CDTIReport & msg);

   long getTime();

   private:

   long time;
   std::vector<ResultPlane> planes;
   ResultPlane ownship;

};


#endif //SAA_APPLICATION_TESTCASERESULT_H
