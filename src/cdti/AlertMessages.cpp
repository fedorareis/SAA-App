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
    int posx = report.planes(0).position().x();
    int timestamp = report.timestamp();
    //std::cout << report << std::endl;
    return report;
}

