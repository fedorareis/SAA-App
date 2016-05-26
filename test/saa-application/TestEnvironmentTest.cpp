//
// Created by Kyle Piddington on 5/12/16.
//

#include <gtest/gtest.h>
#include <mocks/MockTestEnvironment.h>
#include <test-server/planes/LinearMotion.h>

using ::testing::_;
TEST(TestEnvironment, TestOwnshipSensor)
{
    MockTestEnvironment mockEnv;
    mockEnv.createSensors();

    TestCase tc;
    EXPECT_CALL(*(mockEnv.testOwnshipSensor), sendData(_,_))
                .Times(5);
    EXPECT_CALL(*(mockEnv.testRadarSensor),close())
                .Times(1);
    EXPECT_CALL(*(mockEnv.testOwnshipSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testTcasSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testAdsbSensor),close())
          .Times(1);

    TestServerPlane ownship;
    ownship.setMotion(LinearMotion(Vector3d(0,0,0),Vector3d(0,0,1)));
    ownship.setTailNumber("N01234");
    ownship.setLatLongAlt(Vector3d(0,0,0));
    ownship.setNorthEastDownVelocity(Vector3d(0,0,1));
    tc.setOwnship(ownship);
    tc.setTotalTime(5);
    tc.setName("Mock test");
    mockEnv.start(tc);
    //Gather sensors at the end.
}

TEST(TestEnvironment, testTcasSensor)
{
    MockTestEnvironment mockEnv;
    mockEnv.createSensors();

    TestCase tc;
    EXPECT_CALL(*(mockEnv.testOwnshipSensor), sendData(_,_))
          .Times(5);
    EXPECT_CALL(*(mockEnv.testTcasSensor), sendData(_,_))
          .Times(5);
    EXPECT_CALL(*(mockEnv.testRadarSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testOwnshipSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testTcasSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testAdsbSensor),close())
          .Times(1);

    TestServerPlane ownship;
    ownship.setMotion(LinearMotion(Vector3d(0,0,0),Vector3d(0,0,1)));
    ownship.setTailNumber("N01234");
    ownship.setLatLongAlt(Vector3d(0,0,0));
    ownship.setNorthEastDownVelocity(Vector3d(0,0,1));
    ownship.setTcasEnabled(true);
    tc.setOwnship(ownship);
    TestServerPlane tcasPlane;
    tcasPlane.setTcasId(2);
    tcasPlane.setRadarId(1);
    tcasPlane.setTcasEnabled(true);
    tcasPlane.setTailNumber("N9999");
    tcasPlane.setMotion(LinearMotion(Vector3d(0,4,0),Vector3d(0,0,1)));
    tcasPlane.setLatLongAlt(Vector3d(0,4,0));
    tcasPlane.setNorthEastDownVelocity(Vector3d(0,0,1));


    TestServerPlane radarPlane;
    radarPlane.setRadarId(2);
    radarPlane.setTcasEnabled(false);
    radarPlane.setTailNumber("N0000");
    radarPlane.setMotion(LinearMotion(Vector3d(0,-4,0),Vector3d(0,0,1)));
    radarPlane.setLatLongAlt(Vector3d(0,-4,0));
    radarPlane.setNorthEastDownVelocity(Vector3d(0,0,1));
    tc.addPlane(radarPlane);
    tc.addPlane(tcasPlane);
    tc.setTotalTime(5);

    tc.setName("tcasPlane test");
    mockEnv.start(tc);
    //Gather sensors at the end.
}

TEST(TestEnvironment, testRadarSensor)
{
    MockTestEnvironment mockEnv;
    mockEnv.createSensors();

    TestCase tc;
    EXPECT_CALL(*(mockEnv.testOwnshipSensor), sendData(_,_))
          .Times(5);
    EXPECT_CALL(*(mockEnv.testRadarSensor), sendData(_,_))
          .Times(10);
    EXPECT_CALL(*(mockEnv.testRadarSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testOwnshipSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testTcasSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testAdsbSensor),close())
          .Times(1);

    TestServerPlane ownship;
    ownship.setMotion(LinearMotion(Vector3d(0,0,0),Vector3d(0,0,1)));
    ownship.setTailNumber("N01234");
    ownship.setLatLongAlt(Vector3d(0,0,0));
    ownship.setNorthEastDownVelocity(Vector3d(0,0,1));
    ownship.setRadarEnabled(true);
    tc.setOwnship(ownship);
    TestServerPlane plane1;
    plane1.setTcasId(2);
    plane1.setRadarId(1);
    plane1.setTcasEnabled(true);
    plane1.setTailNumber("N9999");
    plane1.setMotion(LinearMotion(Vector3d(0,4,0),Vector3d(0,0,1)));
    plane1.setLatLongAlt(Vector3d(0,4,0));
    plane1.setNorthEastDownVelocity(Vector3d(0,0,1));


    TestServerPlane plane2;
    plane2.setRadarId(2);
    plane2.setTcasEnabled(false);
    plane2.setTailNumber("N0000");
    plane2.setMotion(LinearMotion(Vector3d(0,-4,0),Vector3d(0,0,1)));
    plane2.setLatLongAlt(Vector3d(0,-4,0));
    plane2.setNorthEastDownVelocity(Vector3d(0,0,1));
    tc.addPlane(plane1);
    tc.addPlane(plane2);
    tc.setTotalTime(5);

    tc.setName("tcasPlane test");
    mockEnv.start(tc);
    //Gather sensors at the end.
}
TEST(TestEnvironment, testAdsbSensor)
{
    MockTestEnvironment mockEnv;
    mockEnv.createSensors();

    TestCase tc;
    EXPECT_CALL(*(mockEnv.testOwnshipSensor), sendData(_,_))
          .Times(5);
    EXPECT_CALL(*(mockEnv.testAdsbSensor), sendData(_,_))
          .Times(5);
    EXPECT_CALL(*(mockEnv.testRadarSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testOwnshipSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testTcasSensor),close())
          .Times(1);
    EXPECT_CALL(*(mockEnv.testAdsbSensor),close())
          .Times(1);

    TestServerPlane ownship;
    ownship.setMotion(LinearMotion(Vector3d(0,0,0),Vector3d(0,0,1)));
    ownship.setTailNumber("N01234");
    ownship.setLatLongAlt(Vector3d(0,0,0));
    ownship.setNorthEastDownVelocity(Vector3d(0,0,1));
    ownship.setAdsbEnabled(true);
    tc.setOwnship(ownship);
    TestServerPlane plane1;
    plane1.setTcasId(2);
    plane1.setRadarId(1);
    plane1.setAdsbEnabled(true);
    plane1.setTailNumber("N9999");
    plane1.setMotion(LinearMotion(Vector3d(0,4,0),Vector3d(0,0,1)));
    plane1.setLatLongAlt(Vector3d(0,4,0));
    plane1.setNorthEastDownVelocity(Vector3d(0,0,1));


    TestServerPlane plane2;
    plane2.setRadarId(2);
    plane2.setTailNumber("N0000");
    plane2.setMotion(LinearMotion(Vector3d(0,-4,0),Vector3d(0,0,1)));
    plane2.setLatLongAlt(Vector3d(0,-4,0));
    plane2.setNorthEastDownVelocity(Vector3d(0,0,1));
    tc.addPlane(plane1);
    tc.addPlane(plane2);
    tc.setTotalTime(5);

    tc.setName("tcasPlane test");
    mockEnv.start(tc);
    //Gather sensors at the end.
}

