#include"car.hpp"
#include"coder.h"

Car::Car() : pwm_l{ PWM_L }, pwm_r{ PWM_R }, in_l_a{ IN_L_A }, in_l_b{ IN_L_B }, in_r_a{ IN_R_A }, in_r_b{ IN_R_B },
sen(), left_pid(KP_W, KI_W, KD_W, -V_MAX), right_pid(KP_W, KI_W, KD_W, -V_MAX), dire(KP_T, KI_T, KD_T, 0),
tar_v_l{V_MAX * 0.7}, tar_v_r{V_MAX * 0.7}, init_t{micros()} {}

void Car::control()
{
    if (is_end) {
        end();
        return;
    }
    sen.read();
    // sen.cal_e();
    l_v = cal_l_v();
    r_v = cal_r_v();
    // dire.update(sen.e, sen.t);
    // dire.get_output(); //黑线在左时输出正数
    // decide_tar_PID();
    decide_tar_sen();
    // left_pid.update(l_v - tar_v_l, sen.t);
    // right_pid.update(r_v - tar_v_r, sen.t);
    left_pid.update(l_v - tar_v_l);
    right_pid.update(r_v - tar_v_r);
    l_cmd = left_pid.calculate(), r_cmd = right_pid.calculate();
    // data_print();
    send_cmd(l_cmd, r_cmd);
    // send_cmd_test();
    return;
}

void Car::data_print()
{
    Serial.print("TIME::\t");
    Serial.print(micros());
    Serial.print('\t');
    // if (event) {
    //     Serial.print("!!!\tEVEN\t!!!");
    // }
    sen.print();
    // step_print();
    // v_print();
    // dire.print_out();
    // dire.deep_print();
    // tar_print();
    // left_pid.print_out();
    // left_pid.deep_print();
    // right_pid.print_out();
    // right_pid.deep_print();
    // cmd_print();
    Serial.print('\n');
    return;
}

void Car::decide_tar_PID()
{
    tar_v_l = V_MAX;
    tar_v_r = V_MAX;
    if (sen.e < 0) {
        tar_v_l -= 2 * V_MAX * abs(sen.e) / 5;
    }
    else {
        tar_v_r -= 2 * V_MAX * abs(sen.e) / 5;
    }
    return;
}

void Car::decide_tar_sen()
{
    // tar_v_l = V_MAX * 0.7;
    // tar_v_r = V_MAX * 0.7;
    int emerge_l = 0, emerge_r = 0;
    for (int i = 0; i <= 3; ++i) {
        if (1 == sen.data[i]) {
            ++emerge_l;
        }
        if (1 == sen.data[i + 3]) {
            ++emerge_r;
        }
    }
    //到达终点
    if (emerge_l + emerge_r >= 5 && micros() - init_t >= 35 * 1e6) {
        end_t = micros();
        is_end = true;
        tar_v_l = V_MAX * 2;
        tar_v_r = V_MAX * 2;
        return;
    }
    //直角弯
    if (emerge_l >= 3 && micros() - init_t >= 15 * 1e6) {
        tar_v_l = -0.4 * V_MAX;
        tar_v_r = 1.4 * V_MAX;
        return;
    }
    if (emerge_r >= 3 && micros() - init_t >= 15 * 1e6) {
        tar_v_l = 1.4 * V_MAX;
        tar_v_r = -0.4 * V_MAX;
        return;
    }
    // if (1 == sen.data[0]) {
    //     tar_v_l -= V_MAX * 1.3;
    //     tar_v_r -= V_MAX * 0.7;
    //     return;
    // }
    // if (1 == sen.data[7]) {
    //     tar_v_l -= V_MAX * 0.7;
    //     tar_v_r -= V_MAX * 1.3;
    //     return;
    // }
    if (1 == sen.data[0]) {
        tar_v_l = V_MAX * -0.4;
        tar_v_r = V_MAX * 0.6;
        return;
    }
    if (1 == sen.data[6]) {
        tar_v_l = V_MAX * 0.6;
        tar_v_r = V_MAX * -0.4;
        return;
    }
    //二级警报
    if (1 == sen.data[1]) {
        tar_v_l = V_MAX * 0.3;
        tar_v_r = V_MAX * 0.7;
        return;
    }
    if (1 == sen.data[5]) {
        tar_v_l = V_MAX * 0.7;
        tar_v_r = V_MAX * 0.3;
        return;
    }
    //一级警报
    if (1 == sen.data[2]) {
        tar_v_l = V_MAX * 0.8;
        tar_v_r = V_MAX * 1.1;
        return;
    }
    if (1 == sen.data[4]) {
        tar_v_l = V_MAX * 1.1;
        tar_v_r = V_MAX * 0.8;
        return;
    }

    if (1 == sen.data[3]) {
        tar_v_l = V_MAX;
        tar_v_r = V_MAX;
        return;
    } 
}

void Car::tar_print()
{
    Serial.print("target::\t");
    Serial.print(tar_v_l);
    Serial.print('\t');
    Serial.print(tar_v_r);
    Serial.print('\t');
    return;
}

int leagalize(double num)
{
    return (num <= 255 ? num : 255) >= -255 ? (num <= 255 ? num : 255) : -255;
}

void Car::send_cmd(double l_cmd, double r_cmd)
{
    if (l_cmd < 0) {
        digitalWrite(IN_L_A, LOW);
        digitalWrite(IN_L_B, HIGH);
    }
    else {
        digitalWrite(IN_L_A, HIGH);
        digitalWrite(IN_L_B, LOW);
    }
    analogWrite(PWM_L, abs(leagalize(l_cmd)));
    if (r_cmd > 0) {
        digitalWrite(IN_R_A, LOW);
        digitalWrite(IN_R_B, HIGH);
    }
    else {
        digitalWrite(IN_R_A, HIGH);
        digitalWrite(IN_R_B, LOW);
    }
    analogWrite(PWM_R, abs(leagalize(r_cmd)));
    return;
}

void Car::end()
{
    long now_t = micros() - end_t;
    if (now_t < END_DELAY * 1e6) {
        digitalWrite(IN_L_A, HIGH);
        digitalWrite(IN_L_B, LOW);
        digitalWrite(IN_R_A, LOW);
        digitalWrite(IN_R_B, HIGH);
        analogWrite(PWM_L, 100);
        analogWrite(PWM_R, 100);
        return;
    }
    else if (now_t < (END_TURN + END_DELAY) * 1e6) {
        digitalWrite(IN_L_A, LOW);
        digitalWrite(IN_L_B, HIGH);
        digitalWrite(IN_R_A, LOW);
        digitalWrite(IN_R_B, HIGH);
        analogWrite(PWM_L, 255);
        analogWrite(PWM_R, 255);
        return;
    }
    analogWrite(PWM_L, 0);
    analogWrite(PWM_R, 0);
    base.write(BASE_HORI);
    paw.write(PAW_OPEN);
    return;
}

void Car::send_cmd_test()
{
    // static long last = micros();
    // bool flag1 = HIGH, flag2 = LOW;
    // if ((micros() - last) / 1e6 > 3) {
    //     last = micros();
    //     flag1 = !flag1;
    //     flag2 = !flag2;
    // }
    // analogWrite(PWM_L, 255);
    // analogWrite(PWM_R, 255);
    // digitalWrite(IN_L_A, HIGH);
    // digitalWrite(IN_L_B, LOW);
    // digitalWrite(IN_R_A, LOW);
    // digitalWrite(IN_R_B, HIGH);
    // delay(3000);
    // analogWrite(PWM_L, 75);
    // analogWrite(PWM_R, 75);
    // delay(3000);
    static bool flag = true;
    static int v = 0;
    if (flag) {
        // analogWrite(PWM_L, ++v);
        analogWrite(PWM_R, ++v);
        digitalWrite(IN_L_A, HIGH);
        digitalWrite(IN_L_B, LOW);
        digitalWrite(IN_R_A, LOW);
        digitalWrite(IN_R_B, HIGH);
        if (v > 255) {
            flag = !flag;
        }
    }
    else {
        // analogWrite(PWM_L, abs(--v));
        analogWrite(PWM_R, abs(--v));
        digitalWrite(IN_L_A, HIGH);
        digitalWrite(IN_L_B, LOW);
        digitalWrite(IN_R_A, LOW);
        digitalWrite(IN_R_B, HIGH);
        if (v < 0) {
            flag = !flag;
        }
    }
    return;
}

void Car::cmd_print()
{
    Serial.print("cmd::\t");
    Serial.print(leagalize(l_cmd));
    Serial.print('\t');
    Serial.print(leagalize(r_cmd));
    Serial.print('\t');
}