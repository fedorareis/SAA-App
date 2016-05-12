//
// Created by Kyle Piddington on 4/7/16.
//

#include <gtest/gtest.h>
#include "saa-application/MeanShiftCorrelation.h"


TEST(MeanshiftCorrelator,emptyCorrelation)
{
    MeanShiftCorrelation correlation;
    auto res = correlation.correlate(std::vector<SensorData>());
    ASSERT_EQ(res.size(),0);
}

TEST(MeanshiftCorrelator, oneDatapoint)
{
    MeanShiftCorrelation correlation;
    std::vector<SensorData> data;

    SensorData data1("",5.01,3,   -400,3000,2050,1020,Sensor::adsb,0,1.0);
    data.push_back(data1);
    auto res = correlation.correlate(data);
    ASSERT_EQ(res.size(),1);

}

TEST(MeanshiftCorrelator,Simple)
{
    MeanShiftCorrelation correlation;
    std::vector<SensorData> data;

    SensorData data1("",5.01,3,   -400,3000,2050,1020,Sensor::adsb,0,1.0);
    SensorData data2("",5,   3.01,-390,3010,2050,1030,Sensor::tcas,0,1.0);
    SensorData data3("",4.99,2.99,-410,2990,2050,1040,Sensor::radar,0,1.0);
    data.push_back(data1);
    data.push_back(data2);
    data.push_back(data3);
    auto res = correlation.correlate(data);
    ASSERT_EQ(res.size(),1);



}

TEST(MeanshiftCorrelator,velocity)
{
    MeanShiftCorrelation correlation(0.0,COR_POS | COR_VEL);
    std::vector<SensorData> data;

    SensorData data1("",5.01,3,   -400,3000,2050,1020,Sensor::adsb,0,1.0);
    SensorData data2("",5,   3.01,-390,3010,2050,1030,Sensor::tcas,0,1.0);
    SensorData data3("",4.99,2.99,-410,2990,2050,1040,Sensor::radar,0,1.0);
    data.push_back(data1);
    data.push_back(data2);
    data.push_back(data3);
    auto res = correlation.correlate(data);
    ASSERT_EQ(res.size(),1);
}

TEST(MeanshiftCorrelator,velocity2)
{
    MeanShiftCorrelation correlation(0.0,COR_POS | COR_VEL);
    std::vector<SensorData> data;

    SensorData data1("",5.01,3,   -400,3000,2050,1020,Sensor::adsb,0,1.0);
    SensorData data2("",5,   3.01,-390,3010,2050,1030,Sensor::tcas,0,1.0);
    //Third plane should be going the opposite way.
    SensorData data3("",4.5,2.5,-410,-2990,-2050,-1040,Sensor::radar,0,1.0);
    data.push_back(data1);
    data.push_back(data2);
    data.push_back(data3);
    auto res = correlation.correlate(data);
    ASSERT_EQ(res.size(),2);
}



