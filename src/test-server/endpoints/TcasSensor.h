//
// Created by Kyle Piddington on 1/26/16.
//

#ifndef SAA_APPLICATION_TCASSENSOR_H
#define SAA_APPLICATION_TCASSENSOR_H

#include <test-server/planes/TestServerPlane.h>
#include "common/protobuf/tcas.pb.h"
#include "SensorEndpoint.h"
#include "Sensor.h"

class TcasSensor : public Sensor {
   public:
   TcasSensor(SensorEndpoint * endpoint);
   private:
   virtual void sendData(const TestServerPlane &plane, const TestServerPlane & other);

   static TcasReport createReport(const TestServerPlane & plane, const TestServerPlane & ownship);
};


#endif //SAA_APPLICATION_TCASSENSOR_H
