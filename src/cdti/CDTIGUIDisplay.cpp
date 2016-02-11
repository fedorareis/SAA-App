#include <QtWidgets/qlabel.h>
#include <QtWidgets/qscrollarea.h>
#include <iostream>
#include "CDTIGUIDisplay.h"

Proximate* CDTIGUIDisplay::proximateImage = nullptr;
Resolution* CDTIGUIDisplay::resolutionImage = nullptr;
Traffic* CDTIGUIDisplay::trafficImage = nullptr;
Ownship* CDTIGUIDisplay::ownshipImage = nullptr;

CDTIGUIDisplay::CDTIGUIDisplay(int width, int height): width(width), height(height)
{
    resize(width, height);

    trafficImage = new Traffic(100,100);
    proximateImage = new Proximate(100,100);
    resolutionImage = new Resolution(100,100);
    ownshipImage = new Ownship(100,100);
}

CDTIGUIDisplay::CDTIGUIDisplay(): CDTIGUIDisplay(1280, 720)
{
    std::string filepath = __FILE__;
    filepath = filepath.substr(0,filepath.rfind("/") + 1) .append("../..");
    QDir projectDir(filepath.c_str());
}

void CDTIGUIDisplay::setupLayout()
{
    QPalette Pal(palette());
    //set backgroud color
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void CDTIGUIDisplay::paintEvent(QPaintEvent *event)
{
    //TODO Move to airplane implementation?
    //setup loading directory
    //render ownship

    //render gridlines
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
    //render ownship. everything is relative to it, so it never moved from the center
    if(ownshipImage)
    {
        ownshipImage->draw(this,width / 2,height / 2);
    }


    //if there is a report to be read, attempt to render planes here
    if(currentReport)
    {

        for(int i = 0; i < currentReport->planes_size(); i++)
        {
            CDTIPlane report = currentReport->planes(i);
            PlaneImage* currentImage;
            switch(report.severity())
            {
                case CDTIPlane_Severity_PROXIMATE:
                    currentImage = proximateImage;
                    break;
                case CDTIPlane_Severity_RESOLUTION:
                    currentImage = resolutionImage;
                    break;
                case CDTIPlane_Severity_TRAFFIC:
                    currentImage = trafficImage;
                    break;
            }
            //render planes here
            if(currentImage)
                currentImage->draw(this,width / 2.0f + report.position().x() * 20.0f,height / 2.0f - report.position().y() * 20.0f);
        }
    }
}

void CDTIGUIDisplay::init()
{
    setupLayout();
    show();
}

void CDTIGUIDisplay::renderReport(CDTIReport &report)
{
    currentReport = &report;
}
