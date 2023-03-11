#ifndef _PID_
#define _PID_

#include"const.hpp"

class PID {
protected:
    double e[3]; //下标越小越新
    double de;
    double Ie;
    long t[3]; //下标越小越新
    double KP, KI, KD;
    double out;
public:
    PID(double kp, double ki, double kd, double e0);
    void update(double now_e, double now_t);
    void update(double now_e);
    double get_output();
    double calculate();
    void print_out();
    void deep_print();
};

#endif