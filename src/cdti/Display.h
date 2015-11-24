#ifndef SAA_APPLICATION_DISPLAY_CDTI_H
#define SAA_APPLICATION_DISPLAY_CDTI_H

#include <QtWidgets>

class Display: public QMainWindow
{
    Q_OBJECT
private:
    const int width, height;
public:
    Display();
    Display(int width, int height);

    void setupLayout();

    const int getWidth() const{return width;}
    const int getHeight() const{return height;}
};
#endif //SAA_APPLICATION_DISPLAY_CDTI_H