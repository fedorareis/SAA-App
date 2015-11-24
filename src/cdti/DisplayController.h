#ifndef SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H
#define SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H

#include <QtWidgets/qwidget.h>
#include "Display.h"

class DisplayController
{
private:
    Display& display;
public:
    DisplayController(Display& dipslay);
    void run();
};
#endif //SAA_APPLICATION_DISPLAYCONTROLLER_CDTI_H