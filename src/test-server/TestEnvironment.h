//
// Created by Kyle Piddington on 11/24/15.
//

#ifndef SAA_APPLICATION_TESTENVIRONMENT_H
#define SAA_APPLICATION_TESTENVIRONMENT_H

#include <test-server/endpoints/SocketSensorEndpoint.h>
#include "test-server/endpoints/SensorEndpoint.h"
#include "test-server/endpoints/Sensor.h"
#include "test-server/endpoints/AdsbSensor.h"
#include "test-server/endpoints/OwnshipSensor.h"
#include "TestCase.h"
#include <test-server/endpoints/TcasSensor.h>
#include <test-server/endpoints/RadarSensor.h>

class TestEnvironment {
   public:
      TestEnvironment();
      bool acceptConnections();
      void start(TestCase & tc);

   protected:
      virtual void createSensors();
      std::shared_ptr<Sensor> adsbSensor;// = AdsbSensor(new SocketSensorEndpoint());
      std::shared_ptr<Sensor> ownshipSensor;// = OwnshipSensor(new SocketSensorEndpoint());
      std::shared_ptr<Sensor> tcasSensor;// = TcasSnsor(new SocketSensorEndpoint());
      std::shared_ptr<Sensor> radarSensor;// = RadarSensor(new SocketSensorEndpoint());

      std::shared_ptr<ClientSocket> cdtiSocket;
      bool delay;

};


#endif //SAA_APPLICATION_TESTENVIRONMENT_H
