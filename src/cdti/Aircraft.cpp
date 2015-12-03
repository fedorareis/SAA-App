#include <QtCore/qdir.h>
#include <QtGui/qimagereader.h>
#include <iostream>
#include "Aircraft.h"

QImage Aircraft::getSeverityImage()
{
    //load image
    QImage finalImage;
    QDir projectDir(".");
    projectDir.cdUp();
    projectDir.cdUp();

    QImageReader imageReader(projectDir.filePath("resources/proximate.png"));
    //imageReader.setScaledSize(QSize(25,25));
    QImage image1 = imageReader.read();
    imageReader.setFileName(projectDir.filePath("resources/traffic.png"));
    QImage image2 = imageReader.read();
    imageReader.setFileName(projectDir.filePath("resources/resolution.png"));
    QImage image3 = imageReader.read();

    image1 = image1.scaled(100,100,Qt::IgnoreAspectRatio);
    image2= image2.scaled(100,100,Qt::IgnoreAspectRatio);
    image3 = image3.scaled(100,100,Qt::IgnoreAspectRatio);

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
    severity = plane.severity();
    position = plane.position();
    velocity = plane.velocity();
    //open image and scale it
    image = getSeverityImage();
    //image = image.scaled(100,100,Qt::IgnoreAspectRatio);
}
