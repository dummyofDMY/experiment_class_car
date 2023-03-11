#include"PID.hpp"

PID::PID(double kp, double ki, double kd, double e0) : KP{ kp }, KI{ ki }, KD{ kd } {
    for (int i = 0; i < 3; ++i) {
        e[i] = e0;
        t[i] = micros();
        for (int j = 0; j < 1000; ++j);
    }
    out = 0;
}

void PID::update(double now_e, double now_t)
{
    for (int i = 1; i >= -1; --i) {
        e[i + 1] = e[i];
        t[i + 1] = t[i];
    }
    e[0] = now_e;
    t[0] = now_t;
    return;
}

void PID::update(double now_e)
{
    for (int i = 1; i >= -1; --i) {
        e[i + 1] = e[i];
    }
    e[0] = now_e;
    return;
}

double PID::get_output()
{
    out = 0;
    de = (e[0] - e[1]) / (t[0] - t[1]) * 1e6;
    Ie = (e[0] + e[1] + e[2]) * (t[0] - t[2]) / 1e6;
    return out = -KP * e[0] - KI * Ie - KD * de;
}

double PID::calculate()
{
    out = 0;
    de = (e[0] - e[1]) / PERIOD;
    Ie = (e[0] + e[1] + e[2]) * PERIOD * 2;
    return out = -KP * e[0] - KI * Ie - KD * de;
}

void PID::print_out()
{
    Serial.print("PID::e[3]:t[3]:out\t");
    for (int i = 0; i < 3; ++i) {
        Serial.print(e[i]);
        Serial.print('\t');
    }
    for (int i = 0; i < 3; ++i) {
        Serial.print(t[i]);
        Serial.print('\t');
    }
    Serial.print(out);
    Serial.print('\t');
}

void PID::deep_print()
{
  Serial.print("PID_deep::e[0]:de:Ie\t");
  Serial.print(e[0]);
  Serial.print('\t');
  Serial.print(de);
  Serial.print('\t');
  Serial.print(Ie);
  Serial.print('\t');
}