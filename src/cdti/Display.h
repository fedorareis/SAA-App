#ifndef SAA_APPLICATION_DISPLAY_CDTI_H
#define SAA_APPLICATION_DISPLAY_CDTI_H

#include <QtWidgets>
#include "Aircraft.h"

class Display: public QMainWindow
{
    Q_OBJECT
private:
    const int width, height;
    const int numGridCircles = 5;
    std::vector<Aircraft *> planes;
public:
    Display();
    Display(int width, int height);

    void setupLayout();
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void addPlane(Aircraft* plane){planes.push_back(plane);}
    Aircraft* getPlane(int i){return planes[i];}
    const int getWidth() const{return width;}
    const int getHeight() const{return height;}
};
#endif //SAA_APPLICATION_DISPLAY_CDTI_H