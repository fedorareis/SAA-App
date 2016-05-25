//
// Created by lejonmcgowan on 5/24/16.
//

#ifndef SAA_APPLICATION_FRAMEBODY_H
#define SAA_APPLICATION_FRAMEBODY_H


#include "Maths.h"
#include <glm/gtx/transform.hpp>

class FrameBody
{
private:
    BodyBasis bodyBasis;
    Vector3d lla;
    glm::dmat4 _tx;
    glm::dmat4 _utx;
    inline glm::dvec4 basisToVec4(Vector3d axis) {
        return glm::dvec4(axis.x, axis.y, axis.z, 0);
    }
    inline BodyBasis makeRot(glm::dmat4 tx, BodyBasis basis)
    {
        glm::dvec4 result = tx * basisToVec4(bodyBasis.forward);
        Vector3d tempforward = Vector3d(result.x,result.y,result.z);

        result = tx * basisToVec4(bodyBasis.right);
        Vector3d tempRight= Vector3d(result.x,result.y,result.z);

        result = tx * basisToVec4(bodyBasis.down);
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
    FrameBody(Vector3d lla, BodyBasis bodyBasis):lla(lla),bodyBasis(bodyBasis)
    {
        auto xyz = llaToXyz(lla);
        glm::dvec3 p_EB_E = glm::dvec3(xyz.x, xyz.y, xyz.z);
        glm::dvec3 p_BE_B = -1.0 * p_EB_E;

        glm::dmat4 translate = glm::translate(p_EB_E);
        glm::dmat4 uTranslate = glm::translate(p_BE_B);

        double angleZ = -degToRad(atan2(bodyBasis.forward.y,bodyBasis.forward.x));
        glm::dmat4 rotZ = glm::rotate(angleZ,glm::dvec3(0,0,0));
        glm::dmat4 uRotZ = glm::rotate(-angleZ,glm::dvec3(0,0,0));

        BodyBasis tempBasis = makeRot(rotZ,bodyBasis);


        double angleY = -degToRad(atan2(tempBasis.forward.z,tempBasis.forward.x));
        glm::dmat4 rotY = glm::rotate(angleY,glm::dvec3(0,0,0));
        glm::dmat4 uRotY = glm::rotate(-angleY,glm::dvec3(0,0,0));

        tempBasis = makeRot(rotY,tempBasis);

        double angleX = -degToRad(atan2(tempBasis.right.z,tempBasis.right.y));
        glm::dmat4 rotX = glm::rotate(angleY,glm::dvec3(0,0,0));
        glm::dmat4 uRotX = glm::rotate(-angleY,glm::dvec3(0,0,0));

        _tx = translate * rotZ * rotY * rotX;
        _utx = uRotX * uRotY * uRotZ * uTranslate;
    }



    Vector3d tx(Vector3d vec)
    {
        return txInternal(vec,_tx);
    }

    Vector3d utx(Vector3d vec)
    {
        return txInternal(vec,_utx);
    }
};


#endif //SAA_APPLICATION_FRAMEBODY_H
