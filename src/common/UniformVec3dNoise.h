//
// Created by Kyle Piddington on 4/12/16.
//

#ifndef SAA_APPLICATION_UNIFORMVEC3DNOISE_H
#define SAA_APPLICATION_UNIFORMVEC3DNOISE_H
#include <random>
#include "maths.h"

#include "Vec3dNoise.h"
#include "Randomizer.h"

class UniformVec3dNoise : public Vec3dNoise {
   public:
    UniformVec3dNoise(Vector3d min, Vector3d max);
    Vector3d getNoise();

   private:
   Randomizer rndX;
   Randomizer rndY;
   Randomizer rndZ;


};


#endif //SAA_APPLICATION_UNIFORMVEC3DNOISE_H
