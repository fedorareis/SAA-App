/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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