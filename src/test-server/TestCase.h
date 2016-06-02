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
// Created by Hae Ri Hwang on 11/24/15.
//

#ifndef SAA_APPLICATION_TESTCASE_H
#define SAA_APPLICATION_TESTCASE_H

#include <iosfwd>
#include <test-server/planes/TestServerPlane.h>
#include <vector>
#include <common/Randomizer.h>

class TestCase
{

public:
    TestCase();

    TestCase(const TestCase &otherTestCase);

    /**
     * Set the name of the test case
     */
    void setName(const std::string name);

    void setTotalTime(float totalTime);

    /**
     * Set the ownship data of the test case
     */
    void setOwnship(const TestServerPlane &plane);

    /**
     * Add a plane to the test case
     */
    void addPlane(const TestServerPlane &plane);

    /**
     * Retreieve the ownship a a certain time (1 tick = 10seconds)
     */
    void update(float dt);

    const TestServerPlane &getOwnship() const;

    /**
     * Retrieve all the planes at a certain time(1 tick = 10 seconds)
     */
    const std::vector<TestServerPlane> &getPlanes() const;

    void complete();

    bool isRunning();

    int getNextTcasId();

    int getNextRadarId();

    int getNextPlaneId();

   int getTotalTime() const;
   int getElapsedTime() const;

    /**
     * enables or disables data fuzzing of planes for the test case
     */
    void makeDataNoise(bool noise);

    bool getNoiseEnabled() const;

private:
    static Randomizer *sensorNoise;
    bool enableErrors;
    float totalTime;

    float t;
    TestServerPlane ownship;
    std::vector<TestServerPlane> otherPlanes;
    std::string name;

    int radarId;
    int tcasId;
    int planeId;
};

#endif //SAA_APPLICATION_TESTCASE_H
