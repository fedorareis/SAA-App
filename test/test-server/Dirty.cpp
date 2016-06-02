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

