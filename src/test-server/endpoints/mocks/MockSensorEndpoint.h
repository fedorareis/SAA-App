//
// Created by Kyle Piddington on 11/30/15.
//

#ifndef SAA_APPLICATION_MOCKSENSORENDPOINT_H
#define SAA_APPLICATION_MOCKSENSORENDPOINT_H

#include <test-server/endpoints/SensorEndpoint.h>

class MockSensorEndpoint : public SensorEndpoint
{
   public:
   MockSensorEndpoint();
   virtual  ~MockSensorEndpoint();
   virtual void accept(SensorEndpoint & endpoint);

   protected:

};
#endif //SAA_APPLICATION_MOCKSENSORENDPOINT_H
