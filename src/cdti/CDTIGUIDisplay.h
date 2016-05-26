#ifndef SAA_APPLICATION_DISPLAY_CDTI_H
#define SAA_APPLICATION_DISPLAY_CDTI_H

#include <QtWidgets>
#include <mutex>
#include "Display.h"
#include "Proximate.h"
#include "Resolution.h"
#include "Traffic.h"
#include "Ownship.h"
#include "Air.h"

class CDTIGUIDisplay : private QMainWindow, public Display
{
    Q_OBJECT
private:
    const int width, height;
    const int numGridCircles = 5;
    CDTIReport reportData;
    CDTIReport* currentReport = nullptr;

    static Proximate* proximateImage;
    static Resolution* resolutionImage;
    static Traffic* trafficImage;
    static Ownship* ownshipImage;
    static Air* airImage;

    void setupLayout();
    void paintEvent(QPaintEvent* event) override;
    float scale = 20.0f;
    std::mutex mtx;
public:
    /**
     * initializes a display with the default resolution of 1280 x 720
     */
    CDTIGUIDisplay();
    /**
     * initializes a display with eh
     *
     * @param width: the width of the window to be created
     * @param height: the height of the window to be created
     */
    CDTIGUIDisplay(int width, int height);

    void init() override;
    void renderReport(CDTIReport& report) override;
    virtual bool event(QEvent* event) override;

};
#endif //SAA_APPLICATION_DISPLAY_CDTI_H