#include"PID.hpp"
#include"car.hpp"
#include"const.hpp"
#include<MsTimer2.h>
#include<Servo.h>

Servo base, paw;
Car car;

extern void run()
{
  car.control();
  return;
}

void pick()
{
  paw.write(PAW_OPEN);
  delay(500);
  base.write(BASE_HORI);
  delay(500);
  paw.write(PAW_CLOSE);
  delay(500);
  base.write(BASE_VER);
}

void setup() {
    pinMode(PWM_L, OUTPUT);
    pinMode(PWM_R, OUTPUT);
    pinMode(IN_L_A, OUTPUT);
    pinMode(IN_L_B, OUTPUT);
    pinMode(IN_R_A, OUTPUT);
    pinMode(IN_R_B, OUTPUT);
    pinMode(SEN0, INPUT);
    pinMode(SEN1, INPUT);
    pinMode(SEN2, INPUT);
    pinMode(SEN3, INPUT);
    pinMode(SEN4, INPUT);
    pinMode(SEN5, INPUT);
    pinMode(SEN6, INPUT);
    pinMode(L_CO_A, INPUT);
    pinMode(L_CO_B, INPUT);
    pinMode(R_CO_A, INPUT);
    pinMode(R_CO_B, INPUT);
    pinMode(BASE_PIN, OUTPUT);
    pinMode(PAW_PIN, OUTPUT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(L_CO_A), l_co_count, RISING);
    attachInterrupt(digitalPinToInterrupt(R_CO_A), r_co_count, RISING);
    base.attach(BASE_PIN);
    paw.attach(PAW_PIN);
    pick();
    MsTimer2::set(PERIOD * 1e3, run);
    MsTimer2::start();
}

void loop() {

}