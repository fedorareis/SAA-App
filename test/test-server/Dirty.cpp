//
// Created by lejonmcgowan on 5/25/16.
//

#include <gtest/gtest.h>
#include <common/FrameBody.h>

using namespace std;

TEST(DirtyTest, testConversions)
{
    Vector3d lla(35,-120,1);
    Vector3d xyz = llaToXyz(lla);
    Vector3d lla2 = xyzToLla(xyz);

    cout << lla << endl;
    cout << xyz << endl;
    cout << lla2 << endl;
}


TEST(DirtyTest, helloWorld)
{
    cout << "Hello World" << endl;
    auto pos = Vector3d(35,-120,0);
    auto nedVel = Vector3d(1, -1, 0);
    auto nedBasis = makeNEDBasis(llaToXyz(pos));

    auto bodyBasis = makeBodyBasis(pos, nedVel);
    cout << "ned basis n:" << nedBasis.north << " e:" << nedBasis.east << " d:" << nedBasis.down << endl;
    cout << "body basis f:" << bodyBasis.forward << " r:" << bodyBasis.right << " d:" << bodyBasis.down << endl;


    FrameBody body(pos, bodyBasis);
    cout << "to body frame from lla " << body.tx(llaToXyz(Vector3d(0, 0, 0))) << endl;
    auto result = body.utx(Vector3d(84.8528,0,0));

    cout << "to lla from body frame " << xyzToLla(result) << endl;

}

