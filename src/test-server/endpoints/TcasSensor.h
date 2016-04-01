//
// Created by Kyle Piddington on 1/26/16.
//

#ifndef SAA_APPLICATION_TCASSENSOR_H
#define SAA_APPLICATION_TCASSENSOR_H

#include <test-server/planes/TestServerPlane.h>
#include "common/protobuf/tcas.pb.h"
#include "SensorEndpoint.h"
#include "Sensor.h"
#include <gtest/gtest.h>

class TcasSensor : public Sensor {
public:
   TcasSensor(SensorEndpoint * endpoint, bool jitter = false);
   virtual void sendData(const TestServerPlane &plane, const TestServerPlane & other);

private:
    TcasReport createReport(const TestServerPlane &plane, const TestServerPlane &ownship);

   FRIEND_TEST(TCAS,createTcasMessage);
   FRIEND_TEST(TCAS,testAltitudeDistance);


};


#endif //SAA_APPLICATION_TCASSENSOR_H
