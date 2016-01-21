#include <QtCore/qdir.h>
#include <QtGui/qimagereader.h>
#include <iostream>
#include "Aircraft.h"

Proximate* Aircraft::proximateImage = nullptr;
Resolution* Aircraft::resolutionImage = nullptr;
Traffic* Aircraft::trafficImage = nullptr;

void Aircraft::setSeverityImage()
{
    switch(severity)
    {
        case CDTIPlane_Severity_PROXIMATE:
            currentImage = proximateImage;
            //std::cout << "proximate" << std::endl;
            break;
        case CDTIPlane_Severity_TRAFFIC:
            currentImage = trafficImage;
            //std::cout << "traffic" << std::endl;
            break;
        case CDTIPlane_Severity_RESOLUTION:
            currentImage = resolutionImage;
            //std::cout << "resolution" << std::endl;
            break;
    }
}

Aircraft::Aircraft(const CDTIPlane &plane)
{
    severity = plane.severity();
    position = plane.position();
    velocity = plane.velocity();
    //open currentImage and scale it
    setSeverityImage();
    //currentImage = currentImage.scaled(100,100,Qt::IgnoreAspectRatio);
}

void Aircraft::draw(QPaintDevice* device, int viewportWidth, int viewportHeight)
{
    if(currentImage)
        currentImage->draw(device,viewportWidth / 2.0f + position.x() * 20.0f,viewportHeight / 2.0f - position.y() * 20.0f);
}
