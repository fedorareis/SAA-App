#ifndef SAA_APPLICATION_DISPLAY_CDTI_H
#define SAA_APPLICATION_DISPLAY_CDTI_H

#include <QtWidgets>

class Display: public QMainWindow
{
    Q_OBJECT
private:
    const int width, height;
    const int numGridCircles = 5;
public:
    Display();
    Display(int width, int height);

    void setupLayout();
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    const int getWidth() const{return width;}
    const int getHeight() const{return height;}
};
#endif //SAA_APPLICATION_DISPLAY_CDTI_H