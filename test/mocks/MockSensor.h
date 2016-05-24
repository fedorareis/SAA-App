//
// Created by Kyle Piddington on 5/13/16.
//

#ifndef SAA_APPLICATION_MOCKADSBSENSOR_H
#define SAA_APPLICATION_MOCKADSBSENSOR_H
#include <gmock/gmock.h>
#include <test-server/endpoints/Sensor.h>
class MockSensor : public Sensor
{
   public:
    MOCK_METHOD2(sendData, void(const TestServerPlane & , const TestServerPlane &));
    MOCK_METHOD0(close,void());
};


#endif //SAA_APPLICATION_MOCKADSBSENSOR_H
