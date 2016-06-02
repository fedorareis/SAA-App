/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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

long TestCaseResult::getTime() const
{
   return time;
}

ResultPlane ResultPlane::fromGoogleProtobuf(const CDTIPlane &msg) {
   ResultPlane resultPlane;
   resultPlane.relativePosition = Vector3d(msg.position().x(),msg.position().y(),msg.position().z());
   resultPlane.nedVelocity = Vector3d(msg.velocity().x(),msg.velocity().y(),msg.velocity().z());
   resultPlane.tag = msg.id();
   resultPlane.severity = msg.severity();
   for(int i = 0; i < msg.planetags_size(); i++)
   {
      resultPlane.planeTags.push_back(msg.planetags(i));
   }
   return resultPlane;
}

Vector3d ResultPlane::getVelocity() const
{
   return nedVelocity;
}

Vector3d ResultPlane::getPosition() const
{
   return relativePosition;
}

std::string ResultPlane::getTag() const
{
   return tag;
}

CDTIPlane_Severity ResultPlane::getSeverity() const
{
   return CDTIPlane_Severity_TRAFFIC;
}

ResultPlane::ResultPlane():
relativePosition(0,0,0),
nedVelocity(0,0,0)
{


}
