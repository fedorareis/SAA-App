#ifndef SAA_APPLICATION_AIRCRAFT_CDTI_H
#define SAA_APPLICATION_AIRCRAFT_CDTI_H

#include <QtGui/qimage.h>
#include <common/protobuf/cdti.pb.h>
#include "PlaneImage.h"
#include "Proximate.h"
#include "Resolution.h"
#include "Traffic.h"

class Aircraft
{

private:
    Vector position, velocity;
    CDTIPlane_Severity severity;
    bool directional;
    PlaneImage* currentImage;
    static Proximate* proximateImage;
    static Resolution* resolutionImage;
    static Traffic* trafficImage;
public:
    static void setProximateImage(Proximate *proxImg)
    {
        proximateImage = proxImg;
    }
    static void setResolutionImage(Resolution *resolutionImage) {
        Aircraft::resolutionImage = resolutionImage;
    }
    static void setTrafficImage(Traffic *trafficImage) {
        Aircraft::trafficImage = trafficImage;
    }
public:
   Aircraft(const CDTIPlane &plane);
   void setSeverityImage();

    void setPosition(const Vector &position)
    {
        Aircraft::position = position;
    }

    void setVelocity(const Vector &velocity)
    {
        Aircraft::velocity = velocity;
    }

    void setSeverity(const CDTIPlane_Severity &severity)
    {
        Aircraft::severity = severity;
    }

    const Vector &getPosition() const
    {
        return position;
    }

    const Vector &getVelocity() const
    {
        return velocity;
    }

    const CDTIPlane_Severity &getSeverity() const
    {
        return severity;
    }

    void draw(QPaintDevice* device,int width, int height);
};

#endif //SAA_APPLICATION_AIRCRAFT_CDTI_H
