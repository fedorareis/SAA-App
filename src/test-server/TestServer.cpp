//
// Created by Kyle Piddington on 11/15/15.
//

#include <iostream>
#include <test-server/endpoints/AdsbSensor.h>
#include <test-server/endpoints/OwnshipSensor.h>
#include "TestServer.h"


SensorEndpoint * TestServer::ownshipSocket = nullptr;
SensorEndpoint * TestServer::adsbSocket = nullptr;
SensorEndpoint * TestServer::tcasSocket = nullptr;
SensorEndpoint * TestServer::radarSocket = nullptr;
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
