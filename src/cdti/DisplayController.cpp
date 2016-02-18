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
       CDTIReport report = messages->getMessage();

//        for(int i = 0; i < report.planes_size(); i++)
//        {
//            if(i >= display.getNumPlanes())
//            {
//                Aircraft* aircraft = new Aircraft(report.planes(i));
//                std::cout << "Planes added!" << std::endl;
//                display.addPlane(aircraft);
//            }
//            else
//            {
//                Aircraft* aircraft = display.getPlane(i);
//                aircraft->setPosition(report.planes(i).position());
//                aircraft->setVelocity(report.planes(i).velocity());
//                aircraft->setSeverity(report.planes(i).severity());
//            }
//        }

        display.renderReport(report);
        sleep(1);
    }
}
