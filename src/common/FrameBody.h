//
// Created by lejonmcgowan on 5/24/16.
//

#ifndef SAA_APPLICATION_FRAMEBODY_H
#define SAA_APPLICATION_FRAMEBODY_H


#include "Maths.h"
#include <glm/gtx/transform.hpp>
#include <gtest/gtest_prod.h>
#include <iostream>

#define GLM_FORCE_RADIANS


class FrameBody
{
private:
    BodyBasis bodyBasis;
    Vector3d lla;
    glm::dmat4 _tx;
    glm::dmat4 _utx;
    glm::dmat4 translate, uTranslate;
    glm::dmat4 alignForwardX, uAlignForwardX;
    glm::dmat4 alignRightY, uAlignRightY;
    inline glm::dvec4 basisToVec4(Vector3d axis) {
        return glm::dvec4(axis.x, axis.y, axis.z, 0);
    }
    inline BodyBasis makeRot(glm::dmat4 tx, BodyBasis basis)
    {
        glm::dvec4 result = tx * basisToVec4(basis.forward);
        Vector3d tempforward = Vector3d(result.x,result.y,result.z);

        result = tx * basisToVec4(basis.right);
        Vector3d tempRight= Vector3d(result.x,result.y,result.z);

        result = tx * basisToVec4(basis.down);
        Vector3d tempDown = Vector3d(result.x,result.y,result.z);

        return BodyBasis(tempforward,tempRight,tempDown);
    }
    Vector3d txInternal(const Vector3d& vec, glm::dmat4 tx)
    {
        glm::dvec4 in(vec.x, vec.y, vec.z, 1.0);
        auto out = tx * in;
        return Vector3d(out.x, out.y, out.z);
    }
public:
    FrameBody(Vector3d lla, BodyBasis bodyBasis);



    Vector3d tx(Vector3d vec)
    {
        // txInternal(vec,_tx);
        glm::dvec4 in(vec.x, vec.y, vec.z, 1.0);
        auto out = translate * in;
        out = alignForwardX * out;
        out = alignRightY * out;
        return Vector3d(out.x, out.y, out.z);
    }

    Vector3d utx(Vector3d vec)
    {
        glm::dvec4 in(vec.x, vec.y, vec.z, 1.0);
        auto out = uAlignRightY * in;
        out = uAlignForwardX * out;
        out = uTranslate * out;

        return Vector3d(out.x, out.y, out.z);
    }

FRIEND_TEST(DitryTest,helloWorld);
};

std::ostream& operator<<(std::ostream& ostream, Vector3d vec);
std::ostream& operator<<(std::ostream& ostream, BodyBasis bodyBasis);


#endif //SAA_APPLICATION_FRAMEBODY_H
