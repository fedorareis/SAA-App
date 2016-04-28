#ifndef SAA_APPLICATION_ADVISORY_CDTI_H
#define SAA_APPLICATION_ADVISORY_CDTI_H
#include "PlaneImage.h"
class Advisory: public PlaneImage
{

public:
    Advisory(int width, int height)
        : PlaneImage("resources/advisory.png","resources/advisory_directional.png",width, height)
    { }
};
#endif //SAA_APPLICATION_ADVISORY_CDTI_H