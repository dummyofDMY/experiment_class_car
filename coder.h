#ifndef _CODER_
#define _CODER_

extern int left_coder = 0;
extern int right_coder = 0;
extern long last_l_t = micros();
extern long last_r_t = micros();
extern double v_l = 0;
extern double v_r = 0;

void l_co_count();
void r_co_count();
void step_print();
void v_print();
double cal_l_v();
double cal_r_v();

#endif