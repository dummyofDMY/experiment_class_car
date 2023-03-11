#ifndef _SENSOR_
#define _SENSOR_

#include"const.hpp"

class Sensor {
public:
    int pins[8];
    int data[8];
    double e; //负数向左偏
    long t;
    Sensor();
    void read();
    void cal_e();
    void print();
};

#endif