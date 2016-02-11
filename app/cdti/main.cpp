#include <QtWidgets>
#include <cdti/CDTIGUIDisplay.h>
#include <cdti/DisplayController.h>

int main(int argv, char **args)
{
   QApplication app(argv, args);

   CDTIGUIDisplay display(800, 800);
   DisplayController displayController(display);
   displayController.run();
   return app.exec();
}