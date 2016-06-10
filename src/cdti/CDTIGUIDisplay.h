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
    int width, height;
    const int numGridCircles = 5;
    // use to scale the display
    float scale = 20.0f;
    CDTIReport reportData;
    CDTIReport* currentReport = nullptr;
    /* for space saving reasons. There only need to use one loaded asset set per plane,
     * so the CDTIGUIDIPLAY is responsible for keeping track of these images.
     */
    static Proximate* proximateImage;
    static Resolution* resolutionImage;
    static Traffic* trafficImage;
    static Ownship* ownshipImage;
    static Air* airImage;

    void setupLayout();
    void paintEvent(QPaintEvent* event) override;

    std::mutex mtx;
    PlaneImage* getSeverityImage(const CDTIPlane& report);
    std::string getplaneTag(const CDTIPlane& report) const;
    void scaleUp();
    void scaleDown();
protected:
    virtual bool event(QEvent* event) override;
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