#include <iostream>
#include "DisplayController.h"

void DisplayController::run()
{
    display.setupLayout();
    display.show();
    std::cout << "DISPLAY RUNNING!" << std::endl;
}

DisplayController::DisplayController(Display& display):display(display)
{

}
