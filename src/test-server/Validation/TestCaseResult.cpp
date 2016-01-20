//
// Created by Kyle Piddington on 1/19/16.
//

#include "TestCaseResult.h"


TestCaseResult TestCaseResult::fromGoogleProtobuf(const CDTIReport &msg) {
   TestCaseResult result;
   if(msg.has_timestamp())
   {
      result.time = msg.timestamp();
   }
   for(int i = 0; i < msg.planes_size(); i++)
   {
      result.planes.push_back(ResultPlane());
   }
   return result;
}

long TestCaseResult::getTime() {
   return time;
}
