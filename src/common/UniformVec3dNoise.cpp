//
// Created by Kyle Piddington on 4/12/16.
//

#include "UniformVec3dNoise.h"

UniformVec3dNoise::UniformVec3dNoise(Vector3d min, Vector3d max):
rndX(min.x,max.x),
rndY(min.y,max.y),
rndZ(min.z,max.z){

}

Vector3d UniformVec3dNoise::getNoise() {
    return Vector3d(rndX.getRandom(),rndY.getRandom(),rndZ.getRandom());
}
