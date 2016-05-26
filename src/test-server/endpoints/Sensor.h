//
// Created by Kyle Piddington on 11/24/15.
//

#ifndef SAA_APPLICATION_SENSOR_H
#define SAA_APPLICATION_SENSOR_H

#include <test-server/endpoints/SensorEndpoint.h>

class Sensor
{

public:
    Sensor():
    endpoint(NULL)
    { };

    virtual ~Sensor()
    {
        if (endpoint != nullptr)
            delete endpoint;
    }

    virtual void close();

    Sensor(SensorEndpoint *endpoint,bool jitter);

    SensorEndpoint &getEndpoint();

    void setEndpoint(SensorEndpoint *endpoint)
    { this->endpoint = endpoint; }

   void setJitter(bool jitter);

   virtual void sendData(const TestServerPlane &plane, const TestServerPlane &other) = 0;

protected:
    bool jitter;
private:

    SensorEndpoint *endpoint;
};

#endif //SAA_APPLICATION_SENSOR_H
