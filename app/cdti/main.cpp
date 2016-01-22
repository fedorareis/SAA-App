#include <QtWidgets>
#include <cdti/Display.h>
#include <cdti/DisplayController.h>

int main(int argv, char **args)
{
   QApplication app(argv, args);

   Display display(800,800);
   DisplayController displayController(display);
   displayController.run();
   return app.exec();
}