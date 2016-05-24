//
// Created by Kyle Piddington on 5/12/16.
//

#include "MockTestEnvironment.h"

void MockTestEnvironment::createSensors() {
    adsbSensor = testAdsbSensor = std::make_shared<MockSensor>();
    tcasSensor =  testTcasSensor = std::make_shared<MockSensor>();
    ownshipSensor = testOwnshipSensor = std::make_shared<MockSensor>();
    radarSensor = testRadarSensor = std::make_shared<MockSensor>();
    cdtiSocket = nullptr;
}
