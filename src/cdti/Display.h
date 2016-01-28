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
    /**
     * initializes a display with the default resolution of 1280 x 720
     */
    Display();
    /**
     * initializes a display with eh
     *
     * @param width: the width of the window to be created
     * @param height: the height of the window to be created
     */
    Display(int width, int height);

    /**
     * intializes paramaters needed to render images, grid lines, etc.
     */
    void setupLayout();

    /**
     *implements rendering procedure. all draw/rendering methods must be called in the function
     */
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

    /**
     * add a new aircraft to the display.
     *
     * @param plane: the Aircraft to add
     */
    void addPlane(Aircraft* plane){planes.push_back(plane);}

    /**
     * query method for the plane in the display
     *
     * @param i: the index of the plane to retrieve
     *
     * @return: the aircraft at the specified index
     * TODO: add some kind of IndexOutofBoundsException equivalent
     */
    Aircraft* getPlane(int i){return planes[i];}
    /**
     * query method for the width of the window
     *
     * @return: the width of the window
     */
    int getNumPlanes() const
    {
        return (int) planes.size();
    }
    const int getWidth() const{return width;}
    /**
     * query method for the height of the window
     *
     * @return the height of the window
     */
    const int getHeight() const{return height;}
};
#endif //SAA_APPLICATION_DISPLAY_CDTI_H