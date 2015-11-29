//
// Created by Kyle Piddington on 11/15/15.
//

#include <iostream>
#include "TestServer.h"

ServerSocket * TestServer::adsbSocket = nullptr;
ServerSocket * TestServer::ownshipSocket = nullptr;
ServerSocket * TestServer::tcasSocket = nullptr;
ServerSocket * TestServer::radarSocket = nullptr;

ServerSocket *TestServer::getOwnshipSocket() {
    return ownshipSocket;
}
ServerSocket *TestServer::getAdsbSocket() {
    return adsbSocket;
}
ServerSocket * TestServer::getTcasSocket() {
    return tcasSocket;
}
ServerSocket * TestServer::getRadarSocket(){
    return radarSocket;
}
void TestServer::setupSockets(int ownshipPort, int adsbPort, int tcasPort, int radarPort) {
    adsbSocket = new ServerSocket(adsbPort);
    ownshipSocket = new ServerSocket(ownshipPort);
    tcasSocket = new ServerSocket(tcasPort);
    radarSocket = new ServerSocket(radarPort);



}
