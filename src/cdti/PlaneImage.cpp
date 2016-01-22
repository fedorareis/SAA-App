//
// Created by lejonmcgowan on 1/20/16.
//

#include <QtCore/qdir.h>
#include <iostream>
#include "PlaneImage.h"

PlaneImage::PlaneImage(std::string resPath, int width, int height)
{
    std::string projectPath = __FILE__;
    projectPath = projectPath.substr(0, projectPath.rfind("/") + 1) .append("../..");
    QDir projectDir(projectPath.c_str());

    std::cout << projectDir.filePath(resPath.c_str()).toStdString() << std::endl;

    image.load(projectDir.filePath(resPath.c_str()));
    image = image.scaled(width,height);

     //TODO: this should mutate. in case not, well, here's the problem

    imageBrush.setTextureImage(image);

    //init outline to be invisible
    outlinePen.setColor(QColor(0,0,0,0));
    //Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin
    outlinePen.setCapStyle(Qt::RoundCap);
    outlinePen.setJoinStyle(Qt::RoundJoin);
    outlinePen.setStyle(Qt::SolidLine);
    outlinePen.setWidth(4);
}

void PlaneImage::draw(QPaintDevice *window, int posX, int posY)
{
    painter.begin(window);
        painter.setBrush(imageBrush);
        painter.setPen(outlinePen);
        //offset currentImage size
        painter.translate(-image.width() / 2, -image.height() / 2);
        painter.translate(posX,posY);
        painter.drawRect(0,0,image.width(),image.height());
    painter.end();
}

void PlaneImage::setOutlineColor(int red, int green, int blue, int alpha)
{
    outlinePen.setColor(QColor(red,blue,green,alpha));
}

void PlaneImage::setOutlineWidth(int width)
{
    outlinePen.setWidth(width);
}
