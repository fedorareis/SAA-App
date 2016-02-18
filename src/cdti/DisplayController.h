#ifndef SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H
#define SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H

#include <QtWidgets/qwidget.h>
#include <common/sockets/ClientSocket.h>
#include <cdti/endpoints/mocks/CDTIMockEndpoint.h>
#include <thread>
#include "CDTIGUIDisplay.h"
#include "AlertMessages.h"

class DisplayController
{
private:
    Display & display;
    CDTIEndpoint* socket;
    AlertMessages* messages;
    std::thread* socketThread;
public:
    /**
     * constructs a CDTIGUIDisplay controller with the configured display
     *
     * @param display: the display that the controller manages
     */
    DisplayController(Display& dipslay);
    /**
     * starts the update loop
     */
    void run();
    /**
     * method for the polling thread. polls for new reports, and updates the display as naecessary
     */
    void listenOnSocket();
};
#endif //SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H