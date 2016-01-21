#ifndef SAA_APPLICATION_ADVISORY_OWNSHIP_H
#define SAA_APPLICATION_ADVISORY_OWNSHIP_H

#include <QtGui/qimage.h>
#include "Aircraft.h"

class Ownship: public Aircraft
{

public:
    Ownship(const CDTIPlane &plane) : Aircraft(plane) { }
};
#endif //SAA_APPLICATION_ADVISORY_OWNSHIP_H