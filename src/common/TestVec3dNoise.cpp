//
// Created by Kyle Piddington on 4/12/16.
//

#include "TestVec3dNoise.h"

Vector3d TestVec3dNoise::getNoise() {
    return testNoise;
}

TestVec3dNoise::TestVec3dNoise(Vector3d retVal) :
testNoise(retVal){

}
