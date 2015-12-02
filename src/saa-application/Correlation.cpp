//
// Created by Kyle Reis on 11/17/15.
//

#include <iostream>
#include <common/sockets/ClientSocket.h>
#include <common/sockets/SocketException.h>
#include "Correlation.h"
#include "common/protobuf/adsb.pb.h"
#include "common/protobuf/ownship.pb.h"
#include "common/protobuf/radar.pb.h"
#include "common/protobuf/tcas.pb.h"

void Correlation::report()
{
   std::cout << "We are correlating some stuff" << std::endl;
}

std::vector<Plane> Correlation::correlate(std::vector<Plane> planes) {
   return planes;
}