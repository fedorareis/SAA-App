#ifndef SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H
#define SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H

#include <QtWidgets/qwidget.h>
#include <common/sockets/ClientSocket.h>
#include <cdti/endpoints/mocks/CDTIMockEndpoint.h>
#include <thread>
#include "Display.h"
#include "AlertMessages.h"

class DisplayController
{
private:
    Display& display;
    CDTIEndpoint* socket;
    AlertMessages* messages;
    std::thread* socketThread;
public:
    DisplayController(Display& dipslay);
    void run();
    void listenOnSocket();
};
#endif //SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H