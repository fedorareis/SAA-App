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
// Created by Kyle Piddington on 11/15/15.
//

#ifndef SAA_APPLICATION_TESTSERVER_H
#define SAA_APPLICATION_TESTSERVER_H

#include <common/sockets/ServerSocket.h>
#include <test-server/endpoints/SensorEndpoint.h>
#include <common/Randomizer.h>
#include <common/Vec3dNoise.h>

class TestServer
{
public:
    static void provideOwnshipEndpoint(SensorEndpoint *endpoint);

    static void provideAdsbEndpoint(SensorEndpoint *endpoint);

    static void provideTcasEndpoint(SensorEndpoint *endpoint);

    static void provideRadarEndpoint(SensorEndpoint *endpoint);

    static void shutdown();

    void report();

    static SensorEndpoint *getOwnshipSocket();

    static SensorEndpoint *getAdsbSocket();

    static SensorEndpoint *getTcasSocket();

    static SensorEndpoint *getRadarSocket();

    static void useNoise(bool noise);

    static bool hasNoise();

    static Vector3d scrambleADSB(Vector3d position);

    static Vector3d scrambleTCAS(Vector3d position);

    static Vector3d scrambleRadar(Vector3d position);

   static Vec3dNoise * getRadarPositionNoise();

   static Vec3dNoise * getRadarVelocityNoise();

private:
    static SensorEndpoint *ownshipSocket;
    static SensorEndpoint *adsbSocket;
    static SensorEndpoint *tcasSocket;
    static SensorEndpoint *radarSocket;

    //ALL lenght randomizers are in feet, angle-based in degrees
    static Randomizer *tcasRangeNoise;
    static Randomizer *tcasAltitudeNoise;
    static Randomizer *tcasBearingNoise;

    static Randomizer *adsbLatNoise;
    static Randomizer *adsbLongNoise;
    static Randomizer *adsbAltNoise;

    static Vec3dNoise *radarPosNoise;
    static Vec3dNoise *radarVelNoise;

    static bool noiseEnabled;
};

#endif //SAA_APPLICATION_TESTSERVER_H
