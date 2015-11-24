#include <QtWidgets/qlabel.h>
#include "Display.h"

Display::Display(int width, int height):width(width),height(height)
{

}

Display::Display(): Display(1280,720)
{

}

void Display::setupLayout()
{
    const QPixmap pixmap("awesome.png");
    QLabel panel(this);
    panel.setBaseSize(200,200);
    panel.setPixmap(pixmap);
}
