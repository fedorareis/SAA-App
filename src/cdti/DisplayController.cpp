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
#include <iostream>
#include <common/sockets/SocketException.h>
#include "DisplayController.h"


void DisplayController::run()
{
    display.init();
    std::cout << "DISPLAY RUNNING!" << std::endl;
    
    socketThread = new std::thread(std::thread( [this] { this->listenOnSocket(); } ));
}

DisplayController::DisplayController(Display & display): display(display)
{
    //set up socket
    try
    {
        socket = new CDTISocketEndpoint("localhost",6000);
    }
    catch(SocketException exception)
    {
        mock = true;
        std::cout << exception.description() << std::endl;
        std::cout << "falling back to mock data" << std::endl;

        socket = new CDTIMockEndpoint();
    }

    //make AlertMessage
    messages = new AlertMessages(*socket);
}

void DisplayController::listenOnSocket()
{
    while(socket->isRunning())
    {
        CDTIReport report;
        if(mock)
        {
            ((CDTIMockEndpoint *)(messages->getSocket()))->step();
        }
        report = messages->getMessage();

//        if(mock)
//        {
//            for (int i = 0; i < report.planes_size(); i++)
//            {
//                if (i >= display.getNumPlanes())
//                {
//                    Aircraft *aircraft = new Aircraft(report.planes(i));
//                    std::cout << "Planes added!" << std::endl;
//                    display.addPlane(aircraft);
//                }
//                else
//                {
//                    Aircraft *aircraft = display.getPlane(i);
//                    aircraft->setPosition(report.planes(i).position());
//                    aircraft->setVelocity(report.planes(i).velocity());
//                    aircraft->setSeverity(report.planes(i).severity());
//                }
//            }
//        }
        //std::cerr << report.DebugString() << endl;
        display.renderReport(report);
        sleep(1);
    }
}
