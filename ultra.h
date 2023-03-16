#include"const.hpp"

void dodge()
{
    digitalWrite(IN_L_A, HIGH);
    digitalWrite(IN_L_B, LOW);
    analogWrite(PWM_L, 50);
    digitalWrite(IN_R_A, LOW);
    digitalWrite(IN_R_B, HIGH);
    analogWrite(PWM_R, 100);
    delay(3000);
    analogWrite(PWM_L, 100);
    analogWrite(PWM_R, 50);
    delay(3000);
    return;
}

void measure_dis()
{
    static int flag = 0;
    if (++flag < 10) {
        return;
    }
    flag = 0;
    float dis = 1000; //单位厘米
    digitalWrite(TRIG_PIN, LOW); //低高低电平发一个短时间脉冲去 TrigPin
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    dis = pulseIn(ECHO_PIN, HIGH) / 58; //将回波时间换算成 cm
    // dis = (int(dis * 100)) / 100; //保留两位小数
    // Serial.print(cm);
    // Serial.print("cm");
    // Serial.println();
    // delay(1000);
    if (dis <= 50) {
        dodge();
    }
    return;
}