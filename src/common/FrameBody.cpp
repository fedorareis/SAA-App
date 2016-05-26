//
// Created by lejonmcgowan on 5/24/16.
//

#include "FrameBody.h"



FrameBody::FrameBody(Vector3d lla, BodyBasis bodyBasis)
    : lla(lla), bodyBasis(bodyBasis)
{
    auto xyz = llaToXyz(lla);
    glm::dvec3 p_EB_E = glm::dvec3(xyz.x, xyz.y, xyz.z);
    glm::dvec3 p_BE_B = p_EB_E * -1.0;

    translate = glm::translate(p_BE_B);
    uTranslate = glm::translate(p_EB_E);
    double fDotX = Vector3d::Dot(bodyBasis.forward, Vector3d(1,0,0));
    double theta;
    if (fDotX == -1.0) {
        //make theta M_PI
        theta = M_PI;

    }
    else if (fDotX != 1.0) {
        theta = acos(fDotX);
    }
    else {
        theta = 0.0;
    }
    Vector3d rotAxis = Vector3d::cross(bodyBasis.forward, Vector3d(1,0,0));
    alignForwardX = glm::rotate(theta, glm::dvec3(rotAxis.x, rotAxis.y, rotAxis.z));
    uAlignForwardX = glm::rotate(-theta, glm::dvec3(rotAxis.x, rotAxis.y, rotAxis.z));

    BodyBasis tempBasis = makeRot(alignForwardX,bodyBasis);
//    std::cout << tempBasis << std::endl;

    theta = -atan2(tempBasis.right.z, tempBasis.right.y);
    alignRightY = glm::rotate(theta, glm::dvec3(1.0, 0.0, 0.0));
    uAlignRightY = glm::rotate(-theta, glm::dvec3(1.0, 0.0, 0.0));

    tempBasis = makeRot(alignRightY,tempBasis);
//    std::cout << tempBasis << std::endl;



    _tx = translate * alignForwardX * alignRightY;
    _utx = uAlignRightY * uAlignForwardX * uTranslate;
}
std::ostream& operator<<(std::ostream& ostream, Vector3d vec)
{
    ostream << "(" << vec.x << " " << vec.y << " " << vec.z << ")";
    return ostream;
}
std::ostream& operator<<(std::ostream& ostream, BodyBasis bodyBasis)
{
    ostream << bodyBasis.forward << " ";
    ostream << bodyBasis.right << " ";
    ostream << bodyBasis.down;
    return ostream;
}