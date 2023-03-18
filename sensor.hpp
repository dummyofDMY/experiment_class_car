#ifndef _SENSOR_
#define _SENSOR_

#include"const.hpp"

class Sensor {
public:
    int pins[7];
    int data[7];
    double e; //负数向左偏
    long t;
    Sensor();
    void read();
    void cal_e();
    void print();
};

#endif