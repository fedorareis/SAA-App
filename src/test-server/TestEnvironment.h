//
// Created by Kyle Piddington on 11/24/15.
//

#ifndef SAA_APPLICATION_TESTENVIRONMENT_H
#define SAA_APPLICATION_TESTENVIRONMENT_H
#include "test-server/endpoints/SensorEndpoint.h"
#include "test-server/endpoints/Sensor.h"
#include "test-server/endpoints/AdsbSensor.h"
#include "TestCase.h"

class TestEnvironment {
   public:
      TestEnvironment(TestCase  tc);
      bool acceptConnections();
      void start();

   private:
      AdsbSensor adsbSensor;
      TestCase testCase;

};


#endif //SAA_APPLICATION_TESTENVIRONMENT_H
