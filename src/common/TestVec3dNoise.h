//
// Created by Kyle Piddington on 4/12/16.
//

#ifndef SAA_APPLICATION_TESTVEC3DNOISE_H
#define SAA_APPLICATION_TESTVEC3DNOISE_H


#include "Vec3dNoise.h"

/**
 * The TestVec3 noise will return
 * the same noise vector every time it is called;
 */
class TestVec3dNoise : public Vec3dNoise {
   public:
   TestVec3dNoise(Vector3d retVal);
   virtual Vector3d getNoise();
   private:
   Vector3d testNoise;
};


#endif //SAA_APPLICATION_TESTVEC3DNOISE_H
