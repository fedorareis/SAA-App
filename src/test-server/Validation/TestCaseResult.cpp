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
      result.planes.push_back(ResultPlane::fromGoogleProtobuf(msg.planes(i)));
   }
   return result;
}

long TestCaseResult::getTime() {
   return time;
}

ResultPlane ResultPlane::fromGoogleProtobuf(const CDTIPlane &msg) {
   ResultPlane resultPlane;
   resultPlane.relativePosition = Vector3d(msg.position().x(),msg.position().y(),msg.position().z());
   resultPlane.nedVelocity = Vector3d(msg.velocity().x(),msg.velocity().y(),msg.velocity().z());
   resultPlane.tag = msg.id();
   resultPlane.severity = msg.severity();
   return resultPlane;
}

Vector3d ResultPlane::getVelocity() {
   return nedVelocity;
}

Vector3d ResultPlane::getPosition() {
   return relativePosition;
}

std::string ResultPlane::getTag() {
   return tag;
}

CDTIPlane_Severity ResultPlane::getSeverity() {
   return CDTIPlane_Severity_TRAFFIC;
}

ResultPlane::ResultPlane():
relativePosition(0,0,0),
nedVelocity(0,0,0)
{


}
