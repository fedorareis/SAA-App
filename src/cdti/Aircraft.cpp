#include <QtCore/qdir.h>
#include <QtGui/qimagereader.h>
#include <iostream>
#include "Aircraft.h"

QImage Aircraft::getSeverityImage()
{
    //load image
    QImage finalImage;
    QDir projectDir(".");
    //projectDir.cdUp();
    //projectDir.cdUp();

    QImageReader imageReader(projectDir.filePath("resources/proximate.png"));
    QImage image1 = imageReader.read();
    imageReader.setFileName(projectDir.filePath("resources/traffic.png"));
    QImage image2 = imageReader.read();
    imageReader.setFileName(projectDir.filePath("resources/resolution.png"));
    QImage image3 = imageReader.read();

    switch(severity)
    {
        case CDTIPlane_Severity_PROXIMATE:
            finalImage = image1;
            //std::cout << "proximate" << std::endl;
            break;
        case CDTIPlane_Severity_TRAFFIC:
            finalImage = image2;
            //std::cout << "traffic" << std::endl;
            break;
        case CDTIPlane_Severity_RESOLUTION:
            finalImage = image3;
            //std::cout << "resolution" << std::endl;
            break;
    }

    if(image.isNull())
        std::cout << "WHAT HAPPENED: "<< imageReader.errorString().toStdString() << std::endl;

    return finalImage;
}

Aircraft::Aircraft(const CDTIPlane &plane)
{
    //open image and scale it
    image = getSeverityImage();
    image = image.scaled(100,100,Qt::IgnoreAspectRatio);
}
