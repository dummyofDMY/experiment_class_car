#ifndef _CAR_
#define _CAR_

#include"const.hpp"
#include"PID.hpp"
#include"sensor.hpp"
#include"coder.h"

class Car {
private:
    PID left_pid, right_pid, dire;
    Sensor sen;
    int pwm_l, pwm_r, in_l_a, in_l_b, in_r_a, in_r_b;
    int sen_pin[8];
    double patrol_e;
    double l_v, r_v;
    double tar_v_l, tar_v_r;
    int l_cmd, r_cmd;
    bool event;
    void decide_tar_PID();
    void decide_tar_sen();
    void tar_print();
    void cmd_print();
    void send_cmd(double l_cmd, double r_cmd);
    void send_cmd_test();
public:
    Car();
    void control();
    void data_print();
};

#endif