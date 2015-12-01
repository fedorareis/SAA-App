#include <QtCore/qdir.h>
#include <QtGui/qimagereader.h>
#include <iostream>
#include "Aircraft.h"

Aircraft::Aircraft(const CDTIPlane &plane)
{
    //load images
    QDir projectDir(".");
    projectDir.cdUp();
    projectDir.cdUp();
    //open image and scale it
    QImageReader imageReader(projectDir.filePath("resources/advisory.png"));
    image1 = imageReader.read();
    imageReader.setFileName(projectDir.filePath("resources/resolution.png"));
    image2 = imageReader.read();
    imageReader.setFileName(projectDir.filePath("resources/traffic.png"));
    image3 = imageReader.read();

    image1 = image1.scaled(100,100,Qt::IgnoreAspectRatio);
    image2 = image2.scaled(100,100,Qt::IgnoreAspectRatio);
    image3 = image3.scaled(100,100,Qt::IgnoreAspectRatio);

    if(image1.isNull())
        std::cout << "IT'S NO USE: "<< imageReader.errorString().toStdString() << std::endl;
    if(image2.isNull())
        std::cout << "IT'S NO USE: "<< imageReader.errorString().toStdString() << std::endl;
    if(image3.isNull())
        std::cout << "IT'S NO USE: "<< imageReader.errorString().toStdString() << std::endl;
}

QImage Aircraft::getSeverityImage()
{
    QImage finalImage;
    switch(severity)
    {
        case CDTIPlane_Severity::CDTIPlane_Severity_PROXIMATE:
            finalImage = image1;
            //std::cout << "proximate" << std::endl;
            break;
        case CDTIPlane_Severity::CDTIPlane_Severity_RESOLUTION:
            finalImage = image2;
            //std::cout << "resolution" << std::endl;
            break;
        case CDTIPlane_Severity::CDTIPlane_Severity_TRAFFIC:
            finalImage = image3;
            //std::cout << "traffic" << std::endl;
            break;
    }
    return finalImage;
}
