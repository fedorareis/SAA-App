//
// Created by lejonmcgowan on 1/20/16.
//

#ifndef SAA_APPLICATION_PLANEIMAGE_H
#define SAA_APPLICATION_PLANEIMAGE_H


#include <QtGui/qpainter.h>

class PlaneImage
{
private:
    QImage image, dirImage;
    QPainter painter;
    QBrush imageBrush;
    QPen outlinePen; //transparent for now, but can be implemented if desired;
    bool directional;
public:
    PlaneImage(std::string resPath,std::string dirPath, int width, int height);
    void drawPlane(QPaintDevice *window, int posX, int posY, bool directional, float angle = 0, std::string text = "");
    void setOutlineColor(int red, int green, int blue, int alpha);
    void setOutlineWidth(int width);
};


#endif //SAA_APPLICATION_PLANEIMAGE_H
