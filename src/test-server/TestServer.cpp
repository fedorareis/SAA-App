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
Randomizer *TestServer::tcasRangeNoise = new Randomizer(-100, 100);
Randomizer *TestServer::tcasAltitudeNoise = new Randomizer(-125, 125);
Randomizer *TestServer::tcasBearingNoise = new Randomizer(-10, 10);

Randomizer *TestServer::adsbLatNoise = new Randomizer(-0.0001, 0.0001);
Randomizer *TestServer::adsbLongNoise = new Randomizer(-0.0001, 0.0001);;
Randomizer *TestServer::adsbAltNoise = new Randomizer(-50, 50);

Randomizer *TestServer::radarRangeNoise = new Randomizer(-0.0001, 0.0001);
Randomizer *TestServer::radarAzimuthNoise = new Randomizer(-0.0001, 0.0001);
Randomizer *TestServer::radarElevationNoise = new Randomizer(-50, 50);

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
    newPosition.x = adsbLatNoise->getRandom((float) position.x);
    newPosition.y = adsbLongNoise->getRandom((float) position.y);
    newPosition.z = adsbAltNoise->getRandom((float) position.z);

    return newPosition;
}

Vector3d TestServer::scrambleTCAS(Vector3d position)
{
    Vector3d newPosition(0, 0, 0);
    newPosition.x = tcasRangeNoise->getRandom((float) position.x);
    newPosition.y = tcasBearingNoise->getRandom((float) position.y);
    newPosition.z = tcasAltitudeNoise->getRandom((float) position.z);

    return newPosition;
}

Vector3d TestServer::scrambleRadar(Vector3d position)
{
    Vector3d newPosition(0, 0, 0);
    newPosition.x = radarRangeNoise->getRandom((float) position.x);
    newPosition.y = radarAzimuthNoise->getRandom((float) position.y);
    newPosition.z = radarElevationNoise->getRandom((float) position.z);

    return newPosition;
}






