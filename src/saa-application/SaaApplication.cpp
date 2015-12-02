//
// Created by Kyle Piddington on 11/15/15.
//

#include <iostream>
#include <vector>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include <common/protobuf/adsb.pb.h>
#include <common/protobuf/ownship.pb.h>
#include "SaaApplication.h"
#include "Correlation.h"
#include "Decision.h"
#include "Plane.h"

/**
 * Sets up the socket connections to the test server for reading in sensor data.
 */
std::vector <ClientSocket> SocketSetup() {
    std::vector<ClientSocket> v;
    try {
        ClientSocket adsbSock("localhost", 5000);
        v.push_back(adsbSock);
        ClientSocket ownSock("localhost", 6000);
        v.push_back(ownSock);
    }
    catch (SocketException) {
        std::cout << "failed to open socket" << std::endl;
        std::exit(-1);
    }
    return v;
}

/**
 * Takes in an AdsBReport and the OwnshipReport data and returns a vector (a list)
 * containing the adsb data converted to relative position to the ownship in the form of a plane object.
 */
std::vector <Plane> convertToRelative(AdsBReport adsb, OwnshipReport) {
    std::vector<Plane> planes;
    std::string tailNumber = "tempTailNumber";
    int positionX = 1;
    int positionY = 2;
    int positionZ = 3;
    int velocityX = 4;
    int velocityY = 5;
    int velocityZ = 6;
    Plane adsbPlane(tailNumber, positionX, positionY, positionZ, velocityX, velocityY, velocityZ);
    planes.push_back(adsbPlane);
    return planes;
}

void SaaApplication::report()
{
    bool run = true;
    Correlation cor;
    AdsBReport adsb;
    OwnshipReport ownship;

    std::vector<ClientSocket> socks = SocketSetup();
    ClientSocket ownSock = socks.back();
    socks.pop_back();
    ClientSocket adsbSock = socks.back();
    socks.pop_back();

    while(run) {
        try {
            adsbSock.operator>>(adsb);
            ownSock.operator>>(ownship);
            std::vector<Plane> planes = convertToRelative(adsb, ownship);
            //cor.correlate();
        }
        catch (SocketException) {
            run = false;
        }
    }

    std::cout << "Hello from Saa App!" << std::endl;
    //Correlation cor;
    Decision dec;
    cor.report();
    dec.report(&list);
    auto rep = dec.generateReport(&list);
    delete rep;
}


