//
// Created by Kyle Piddington on 11/15/15.
//

#include <test-server/endpoints/AdsbSensor.h>
#include "TestServer.h"


SensorEndpoint * TestServer::ownshipSocket = nullptr;
SensorEndpoint * TestServer::adsbSocket = nullptr;
SensorEndpoint * TestServer::tcasSocket = nullptr;
SensorEndpoint * TestServer::radarSocket = nullptr;

//todo figure out what numbers to put here
Randomizer *TestServer::adsbNoise = new Randomizer(-2, 2);
Randomizer *TestServer::tcasNoise = new Randomizer(-2, 2);
Randomizer *TestServer::radarNoise = new Randomizer(-2, 2);

bool TestServer::noiseEnabled = false;


SensorEndpoint * TestServer::getOwnshipSocket()
{
    return ownshipSocket;
}

SensorEndpoint * TestServer::getAdsbSocket()
{
    return adsbSocket;
}

void TestServer::provideOwnshipEndpoint(SensorEndpoint *endpoint)
{
    TestServer::ownshipSocket = endpoint;
}

void TestServer::provideAdsbEndpoint(SensorEndpoint *endpoint)
{
    TestServer::adsbSocket = endpoint;

}

void TestServer::provideRadarEndpoint(SensorEndpoint * endpoint)
{
    TestServer::radarSocket = endpoint;
}
void TestServer::provideTcasEndpoint(SensorEndpoint * endpoint)
{
    TestServer::tcasSocket = endpoint;
}

void TestServer::shutdown()
{
    if(ownshipSocket != nullptr)
        delete ownshipSocket;
    if(adsbSocket != nullptr)
        delete adsbSocket;
    if(tcasSocket != nullptr)
        delete tcasSocket;
    if(radarSocket != nullptr)
        delete radarSocket;

}

SensorEndpoint *TestServer::getTcasSocket() {
    return tcasSocket;
}

SensorEndpoint *TestServer::getRadarSocket() {
    return radarSocket;
}

void TestServer::useNoise(bool noise)
{
    noiseEnabled = noise;
}

bool TestServer::hasNoise()
{
    return noiseEnabled;
}

Vector3d TestServer::scrambleADSB(Vector3d position)
{
    Vector3d newPosition(0, 0, 0);
    newPosition.x = adsbNoise->getRandom((float) position.x);
    newPosition.y = adsbNoise->getRandom((float) position.y);
    newPosition.z = adsbNoise->getRandom((float) position.z);

    return newPosition;
}

Vector3d TestServer::scrambleTCAS(Vector3d position)
{
    Vector3d newPosition(0, 0, 0);
    newPosition.x = tcasNoise->getRandom((float) position.x);
    newPosition.y = tcasNoise->getRandom((float) position.y);
    newPosition.z = tcasNoise->getRandom((float) position.z);

    return newPosition;
}

Vector3d TestServer::scrambleRadar(Vector3d position)
{
    Vector3d newPosition(0, 0, 0);
    newPosition.x = radarNoise->getRandom((float) position.x);
    newPosition.y = radarNoise->getRandom((float) position.y);
    newPosition.z = radarNoise->getRandom((float) position.z);

    return newPosition;
}






