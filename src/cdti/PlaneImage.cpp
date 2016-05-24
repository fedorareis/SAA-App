//
// Created by lejonmcgowan on 1/20/16.
//

#include <QtCore/qdir.h>
#include <iostream>
#include "PlaneImage.h"

PlaneImage::PlaneImage(std::string resPath, std::string dirPath, int width, int height)
{
    std::string projectPath = __FILE__;
    projectPath = projectPath.substr(0, projectPath.rfind("/") + 1) .append("../..");
    QDir projectDir(projectPath.c_str());

    std::cout << projectDir.filePath(resPath.c_str()).toStdString() << std::endl;

    image.load(projectDir.filePath(resPath.c_str()));
    image = image.scaled(width,height);

    dirImage.load(projectDir.filePath(dirPath.c_str()));
    dirImage = dirImage.scaled(width,height);
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

void PlaneImage::draw(QPaintDevice *window, int posX, int posY, bool directional)
{
    QImage drawImage;
    if(directional)
        drawImage = dirImage;
    else
        drawImage = image;

    painter.begin(window);
        painter.setBrush(imageBrush);
        painter.setPen(outlinePen);
        //offset currentImage size
        painter.translate(-drawImage.width() / 2, -drawImage.height() / 2);
        painter.translate(posX,posY);
        painter.drawRect(0,0,drawImage.width(),drawImage.height());
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
