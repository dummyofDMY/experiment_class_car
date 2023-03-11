#include"coder.h"

void l_co_count()
{
    left_coder += 2 * digitalRead(L_CO_B) - 1;
    return;
}

void r_co_count()
{
    right_coder -= 2 * digitalRead(R_CO_B) - 1;
    return;
}

void step_print()
{
    Serial.print("coder::\t");
    Serial.print(left_coder);
    Serial.print('\t');
    Serial.print(right_coder);
    Serial.print('\t');
}

double cal_l_v()
{
    v_l = left_coder / 780.0 * 3.1415 * 2.0 * 1e6 / (micros() - last_l_t);
    left_coder = 0;
    last_l_t = micros();
    return v_l;
}

double cal_r_v()
{
    v_r = right_coder / 780.0 * 3.1415 * 2.0 * 1e6 / (micros() - last_r_t);
    right_coder = 0;
    last_r_t = micros();
    return v_r;
}

void v_print()
{
    Serial.print("velocity::\t");
    Serial.print(v_l);
    Serial.print('\t');
    Serial.print(v_r);
    Serial.print('\t');
    return;
}