#include <QtWidgets/qlabel.h>
#include <QtWidgets/qscrollarea.h>
#include <iostream>
#include "Display.h"

Display::Display(int width, int height):width(width),height(height)
{
    resize(width, height);

    Aircraft::setTrafficImage(new Traffic(100,100));
    Aircraft::setProximateImage(new Proximate(100,100));
    Aircraft::setResolutionImage(new Resolution(100,100));
}

Display::Display(): Display(1280,720)
{
    std::string filepath = __FILE__;
    filepath = filepath.substr(0,filepath.rfind("/") + 1) .append("../..");
    QDir projectDir(filepath.c_str());
}

void Display::setupLayout()
{
    QPalette Pal(palette());
    //set backgroud color
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void Display::paintEvent(QPaintEvent *event)
{
    //TODO Move to airplane implementation?
    //setup loading directory

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    const QBrush brush();
    painter.setPen(QPen(Qt::white, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.translate(width / 2, height / 2);

    //paint the grid cirlces
    for (int i = 0, radius = 100; i <= numGridCircles; i++, radius += 100.0f)
    {
        painter.drawEllipse(QPointF(0.0f, 0.0f),(float)radius,(float)radius);
    }

    //paint planes

    //paint any other planes in space
    for(auto plane: planes)
    {
       plane->draw(this,width,height);
    }
}
