#include"sensor.hpp"

Sensor::Sensor() : pins{SEN0, SEN1, SEN2, SEN3, SEN4, SEN5, SEN6}, data{ 0 }, e{ 0 } {}

void Sensor::read()
{
    for (int i = 0; i < 7; ++i) {
        data[i] = digitalRead(pins[i]);
    }
    return;
}

void Sensor::cal_e()
{
    e = 0;
    t = micros();
    for (int i = 0; i < 7; ++i) {
        if (1 == data[i]) {
            e += i - 3.5;
        }
    }
    return e;
}

void Sensor::print()
{
    Serial.print("Sensor::\t");
    for (int i = 0; i < 7; ++i) {
        Serial.print(data[i]);
        Serial.print('\t');
    }
    return;
}