//
// Created by Kyle Piddington on 4/12/16.
//

#ifndef SAA_APPLICATION_VEC3DNOISE_H
#define SAA_APPLICATION_VEC3DNOISE_H


#include "Maths.h"

class Vec3dNoise {
   public:
   virtual Vector3d getNoise() = 0;
};


#endif //SAA_APPLICATION_VEC3DNOISE_H
