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
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qscrollarea.h>
#include <iostream>
#include <math.h>
#include "CDTIGUIDisplay.h"
#include <common/Maths.h>
#include <sstream>
#include <boost/algorithm/string.hpp>

Proximate* CDTIGUIDisplay::proximateImage = nullptr;
Resolution* CDTIGUIDisplay::resolutionImage = nullptr;
Traffic* CDTIGUIDisplay::trafficImage = nullptr;
Ownship* CDTIGUIDisplay::ownshipImage = nullptr;
Air* CDTIGUIDisplay::airImage = nullptr;

CDTIGUIDisplay::CDTIGUIDisplay(int width, int height): width(width), height(height)
{
    resize(width, height);
    int size = 80;
    trafficImage = new Traffic(size,size);
    proximateImage = new Proximate(size,size);
    resolutionImage = new Resolution(size,size);
    ownshipImage = new Ownship(size,size);
    airImage = new Air(size,size);
}

CDTIGUIDisplay::CDTIGUIDisplay(): CDTIGUIDisplay(1280, 720)
{
    std::string filepath = __FILE__;
    filepath = filepath.substr(0,filepath.rfind("/") + 1) .append("../..");
    QDir projectDir(filepath.c_str());
}

void CDTIGUIDisplay::setupLayout()
{
    QPalette Pal(palette());
    //set backgroud color
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);
}
void CDTIGUIDisplay::paintEvent(QPaintEvent *event)
{
    //TODO Move to airplane implementation?
    //setup loading directory
    //render ownship
    //render gridlines
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    const QBrush brush();
    painter.setPen(QPen(Qt::white, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.translate(width / 2, height / 2);

    int largerRes = std::max(width,height);
    int numActualCircles = largerRes / 100;
    //paint the grid cirlces
    for (int i = 0, radius = 100; i <= numActualCircles; i++, radius += 100.0f)
    {
        painter.drawEllipse(QPointF(0.0f, 0.0f),(float)radius,(float)radius);
        std::ostringstream out;
        out.precision(2);
        out << radius / scale << " NMI";
        painter.drawText(5+radius,0,QString(out.str().c_str()));
    }

    if (currentReport)
    {
        // paint advisory message
        std::string advMsg = currentReport->advisorymessage();

        QColor penColor(255, 0, 0);

        if (advMsg.compare("Move out of the way") != 0)
        {
            penColor = QColor(255, 255, 255);
        }

        boost::to_upper(advMsg);

        painter.setPen(QPen(penColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        //painter.setBrush(QBrush(QColor(255,255,255)));
        painter.translate(-1 * (width / 4), -1 * (height / 2));
        QRect rect = QRect(0, 0, 400, 75);
        painter.drawText( rect, Qt::AlignCenter, advMsg.c_str() );
        painter.drawRect( rect );
    }

    //render ownship. everything is relative to it, so it never moved from the center
    if (ownshipImage)
    {
        ownshipImage->drawPlane(this, width / 2, height / 2, false);
    }

    //if there is a report to be read, attempt to render planes here
    mtx.lock();
    if (currentReport)
    {
        int planeSize = currentReport->planes_size();
        //render each plane
        for (int i = 0; i < planeSize; i++)
        {
            bool direction = false;
            float angle = 0;
            CDTIPlane report = currentReport->planes(i);
            PlaneImage* currentImage = getSeverityImage(report);

            //check for valid image
            if (currentImage)
            {
                int posX = width / 2.0f - report.position().y() * scale;
                int posY = height / 2.0f - report.position().x() * scale;

                //check for directional planes
                Vector3d vel(report.velocity().x(), report.velocity().y(), report.velocity().z());
                direction = vel.getMagnitude() >= 1e-6;
                std::string tag = "";

                if (direction)
                {
                    angle = radToDeg(atan2(vel.y, vel.x));
                    posX = width / 2.0f + report.position().y() * scale;
                    std::string tag = getplaneTag(report);
                }
                currentImage->drawPlane(this, posX, posY, direction, angle, tag);
            }

        }
    }
    mtx.unlock();
}

PlaneImage* CDTIGUIDisplay::getSeverityImage(const CDTIPlane& report)
{
    PlaneImage* image = nullptr;

    switch (report.severity())
    {
        case CDTIPlane_Severity_RESOLUTION:
            image = resolutionImage;
            break;
        case CDTIPlane_Severity_TRAFFIC:
            image = trafficImage;
            break;
        case CDTIPlane_Severity_AIR:
            image = airImage;
            break;
        case CDTIPlane_Severity_PROXIMATE:
        default:
            image = proximateImage;
            break;
    }

    return image;
}


std::string CDTIGUIDisplay::getplaneTag(const CDTIPlane& report) const
{
    std::string newline = "\r\n";

    //Plane labels -- ID, Position, Velocity, Direction (angle)
    std::ostringstream out;
    out << "ID: " << report.id() << newline;// << "Position: (";
    std::cout.precision(4);
    out << "IDs( ";

    for (int idx = 0; idx < report.planetags_size(); idx++)// plainID : report.planetags())
    {
        out << report.planetags(idx) << " ";
    }
    out << ")" << newline;

    return out.str();
}

void CDTIGUIDisplay::init()
{
    setupLayout();
    show();
}

void CDTIGUIDisplay::renderReport(CDTIReport &report)
{
    mtx.lock();
    CDTIReport copyReport(report);
    reportData = copyReport;
    currentReport = &reportData;
    std::string log(reportData.DebugString());
    mtx.unlock();

    std::cout << log << std::endl;
    update();
}

bool CDTIGUIDisplay::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        if (keyEvent->key() == Qt::Key_Up)
        {
            scaleUp();
        }
        if (keyEvent->key() == Qt::Key_Down)
        {
            scaleDown();
        }
    }
    else if(event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = (QWheelEvent *)event;
        if(wheelEvent->orientation() == Qt::Vertical)
        {
            if (wheelEvent->delta() > 0)
            {
                scaleUp();
            }
            else if(wheelEvent->delta() < 0)
            {
                scaleDown();
            }
        }
    }
    else if(event->type() == QEvent::Resize)
    {
        QResizeEvent *resizeEvent = (QResizeEvent *)event;
        width = resizeEvent->size().width();
        height = resizeEvent->size().height();
    }

    return QMainWindow::event(event);
}

void CDTIGUIDisplay::scaleDown()
{
    scale /= 1.05;
    std::cout << "Scale: " << scale << std::endl;
    update();
}

void CDTIGUIDisplay::scaleUp()
{
    scale *= 1.05;
    std::cout << "Scale: " << scale << std::endl;
    update();
}


