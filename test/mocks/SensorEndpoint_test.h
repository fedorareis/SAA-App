//
// Created by Kyle Piddington on 1/19/16.
//

#ifndef SAA_APPLICATION_SENSORENDPOINT_TEST_H
#define SAA_APPLICATION_SENSORENDPOINT_TEST_H
#include <gmock/gmock.h>
#include <test-server/endpoints/SensorEndpoint.h>

class SensorEndpoint_test :  public SensorEndpoint {
   public:
   SensorEndpoint_test(){};
   virtual ~SensorEndpoint_test(){};

   MOCK_METHOD1(accept,void(SensorEndpoint&));
   MOCK_METHOD0(getSocket,ServerSocket &());


};


#endif //SAA_APPLICATION_SENSORENDPOINT_TEST_H
