#include"const.hpp"

extern bool have_dodge = false;

void dodge()
{
    MsTimer2::stop();
    Serial.print("\n!!!!!DOGGE!!!!!\n");
    //后退
    digitalWrite(IN_L_A, LOW);
    digitalWrite(IN_L_B, HIGH);
    analogWrite(PWM_L, 100);
    digitalWrite(IN_R_A, HIGH);
    digitalWrite(IN_R_B, LOW);
    analogWrite(PWM_R, 100);
    delay(500);
    //左转
    digitalWrite(IN_L_A, LOW);
    digitalWrite(IN_L_B, HIGH);
    analogWrite(PWM_L, 150);
    digitalWrite(IN_R_A, LOW);
    digitalWrite(IN_R_B, HIGH);
    analogWrite(PWM_R, 150);
    delay(180);
    //直行
    digitalWrite(IN_L_A, HIGH);
    digitalWrite(IN_L_B, LOW);
    analogWrite(PWM_L, 100);
    digitalWrite(IN_R_A, LOW);
    digitalWrite(IN_R_B, HIGH);
    analogWrite(PWM_R, 100);
    delay(500);
    //右转
    digitalWrite(IN_L_A, HIGH);
    digitalWrite(IN_L_B, LOW);
    analogWrite(PWM_L, 150);
    digitalWrite(IN_R_A, HIGH);
    digitalWrite(IN_R_B, LOW);
    analogWrite(PWM_R, 150);
    delay(150);
    //直行
    digitalWrite(IN_L_A, HIGH);
    digitalWrite(IN_L_B, LOW);
    analogWrite(PWM_L, 70);
    digitalWrite(IN_R_A, LOW);
    digitalWrite(IN_R_B, HIGH);
    analogWrite(PWM_R, 70);
    delay(1200);
    Sensor tem_sen;
    int emerg = 0;
    do {
        emerg = 0;
        tem_sen.read();
        for (int i = 0; i < 7; ++i) {
            if (1 == tem_sen.data[i]) {
                ++emerg;
            }
        }
    } while(emerg);
    have_dodge = true;
    MsTimer2::start();
    return;
}

void measure_dis()
{
    float dis = 1000; //单位厘米
    digitalWrite(TRIG_PIN, LOW); //低高低电平发一个短时间脉冲去 TrigPin
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    dis = pulseIn(ECHO_PIN, HIGH) / 58; //将回波时间换算成 cm
    Serial.print("dis::\t");
    Serial.print(dis);
    Serial.print("cm\n");
    delay(500);
    if (dis <= 20) {
        dodge();
    }
    return;
}