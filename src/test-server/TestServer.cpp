//
// Created by Kyle Piddington on 11/15/15.
//

#include <iostream>
#include <test-server/endpoints/AdsbSensor.h>
#include <test-server/endpoints/OwnshipSensor.h>
#include "TestServer.h"


SensorEndpoint * TestServer::ownshipSocket = nullptr;
SensorEndpoint * TestServer::adsbSocket = nullptr;

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

void TestServer::shutdown()
{
    if(ownshipSocket != nullptr)
        delete ownshipSocket;
    if(adsbSocket != nullptr)
        delete adsbSocket;
}
