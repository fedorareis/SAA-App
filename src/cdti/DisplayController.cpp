#include <iostream>
#include <common/sockets/SocketException.h>
#include "DisplayController.h"


void DisplayController::run()
{
    display.setupLayout();
    std::cout << "DISPLAY RUNNING!" << std::endl;
    socketThread = new std::thread(std::thread( [this] { this->listenOnSocket(); } ));
}

DisplayController::DisplayController(Display& display):display(display)
{
    //set up socket
    try
    {
        socket = new CDTISocketEndpoint("localhost",6000);
        //socket = new CDTIMockEndpoint();
    }
    catch(SocketException exception)
    {
        std::cout << exception.description() << std::endl;
        std::terminate();
    }

    //make AlertMessage
    messages = new AlertMessages(*socket);
}

void DisplayController::listenOnSocket()
{
    bool initialized = false;
    while(1)
    {
       CDTIReport report = messages->getMessage();
        for(int i = 0; i < report.planes_size(); i++)
        {
            if(!initialized)
            {
                Aircraft* aircraft = new Aircraft(report.planes(i));
                std::cout << "Planes added!" << std::endl;
                display.addPlane(aircraft);
            }
            else
            {
                Aircraft* aircraft = display.getPlane(i);
                aircraft->setPosition(report.planes(i).position());
                aircraft->setVelocity(report.planes(i).velocity());
                aircraft->setSeverity(report.planes(i).severity());
            }
        }
        if(!initialized)
            display.show();

        display.update();
        initialized = true;
        sleep(1);
        //socket->step();
    }
}
