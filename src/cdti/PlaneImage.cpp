/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
//
// Created by lejonmcgowan on 1/20/16.
//

#include <QtCore/qdir.h>
#include <iostream>
#include <common/Maths.h>
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
void PlaneImage::drawPlane(QPaintDevice *window, int posX, int posY, bool directional, float angle, std::string text)
{
    int textMargin = 0;
    QImage drawImage;
    QFont font;

    if(directional)
        drawImage = dirImage;
    else
        drawImage = image;

    imageBrush.setTextureImage(drawImage);

    painter.begin(window);
        painter.resetTransform();
        painter.setBrush(imageBrush);
        painter.setPen(outlinePen);
        //offset currentImage size
        painter.translate(posX,posY);
        painter.save();
        painter.rotate(angle);
        painter.translate(-drawImage.width() / 2, -drawImage.height() / 2);
        painter.drawRect(0,0,drawImage.width(),drawImage.height());
        painter.restore();
        painter.setPen(QColor(255,255,255));
        Vector3d textLocation(drawImage.width() / 2, drawImage.height() / 2, 0);
        int offset(textLocation.getMagnitude() - 10);
        painter.translate(-offset, -offset - textMargin);

        font = painter.font();
        int fontSize = font.pointSize() / 2;
        font.setPointSize(fontSize);
        painter.setFont(font);

        painter.drawText(105, 15, 500, 100, Qt::TextWordWrap, QString(text.c_str()));
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
