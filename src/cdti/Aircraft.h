#ifndef SAA_APPLICATION_AIRCRAFT_CDTI_H
#define SAA_APPLICATION_AIRCRAFT_CDTI_H

#include <QtGui/qimage.h>
#include <common/protobuf/cdti.pb.h>

class Aircraft
{

private:
    Vector position, velocity;
    CDTIPlane_Severity severity;
    QImage image;

public:
   Aircraft(const CDTIPlane &plane);
   QImage getSeverityImage();

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
};

#endif //SAA_APPLICATION_AIRCRAFT_CDTI_H
