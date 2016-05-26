//
// Created by Kyle Piddington on 5/12/16.
//

#ifndef SAA_APPLICATION_MOCKTESTENVIRONMENT_H
#define SAA_APPLICATION_MOCKTESTENVIRONMENT_H

#include <test-server/TestEnvironment.h>
#include "MockSensor.h"
class MockTestEnvironment : public TestEnvironment {
   public:
   MockTestEnvironment():
         TestEnvironment()
   {
       this->delay = false;
   }

   std::shared_ptr<MockSensor> testAdsbSensor;
   std::shared_ptr<MockSensor> testTcasSensor;
   std::shared_ptr<MockSensor> testOwnshipSensor;
   std::shared_ptr<MockSensor> testRadarSensor;
   virtual void createSensors() override;
};


#endif //SAA_APPLICATION_MOCKTESTENVIRONMENT_H
