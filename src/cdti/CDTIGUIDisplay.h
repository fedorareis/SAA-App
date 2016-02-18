#ifndef SAA_APPLICATION_DISPLAY_CDTI_H
#define SAA_APPLICATION_DISPLAY_CDTI_H

#include <QtWidgets>
#include "Display.h"
#include "Proximate.h"
#include "Resolution.h"
#include "Traffic.h"
#include "Ownship.h"

class CDTIGUIDisplay : private QMainWindow, public Display
{
    Q_OBJECT
private:
    const int width, height;
    const int numGridCircles = 5;
    CDTIReport* currentReport;

    static Proximate* proximateImage;
    static Resolution* resolutionImage;
    static Traffic* trafficImage;
    static Ownship* ownshipImage;

    static void setProximateImage(Proximate *proxImg)
    {
        proximateImage = proxImg;
    }
    static void setResolutionImage(Resolution *resolutionImage)
    {
        resolutionImage = resolutionImage;
    }
    static void setTrafficImage(Traffic *trafficImage)
    {
        trafficImage = trafficImage;
    }

    void setupLayout();
    void paintEvent(QPaintEvent* event) override;
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

};
#endif //SAA_APPLICATION_DISPLAY_CDTI_H