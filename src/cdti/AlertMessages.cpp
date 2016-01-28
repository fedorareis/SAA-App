#include <common/sockets/ClientSocket.h>
#include <iostream>
#include "AlertMessages.h"

std::ostream &operator<<(std::ostream& ostream, Vector vector)
{
    ostream << "(" << vector.x()  << "," << vector.y() << ","<< vector.z() << ")";
    return ostream;
}

std::ostream &operator<<(std::ostream& ostream, CDTIPlane plane)
{
    ostream << std::endl << "    ID: " << plane.id() << std::endl;
    ostream << "    Position: " << plane.position() << std::endl;
    ostream << "    Velocity: " << plane.velocity() << std::endl;
    ostream << "    Severity: " << plane.severity();
    return ostream;
}

std::ostream &operator<<(std::ostream& ostream, CDTIReport report)
{
    ostream << "Time: " << report.timestamp() << std::endl;
    ostream << "Ownship: " << report.ownship() << std::endl;
    if(report.has_advisorymessage())
        ostream << "MESSAGE: " << report.advisorymessage() << std::endl;
    if(report.has_advisorylevel())
        ostream << "LEVEL: " << report.advisorylevel() << std::endl;
    for(CDTIPlane plane: report.planes())
        ostream << "Plane: " << plane << std::endl;
    return ostream;
}


AlertMessages::AlertMessages(CDTIEndpoint& socket):cdtiSocket(socket)
{

}

CDTIReport AlertMessages::getMessage()
{
    cdtiSocket >> report;
    //std::cout << report << std::endl;
    return report;
}

