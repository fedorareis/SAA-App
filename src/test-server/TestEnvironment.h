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
