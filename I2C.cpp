#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
const int PowerPin = 23; // 设置GPIO引脚
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// void setPCA9685High(uint8_t num) {
//   pwm.setPWM(num, 4096, 0); 
// }
void PCA9685setup() {
  pinMode(PowerPin, OUTPUT); // 将GPIO引脚设置为输出模式
  digitalWrite(PowerPin, LOW); // 将引脚设置为高电平，输出5v
  Wire.begin(22, 21); // SDA 接GPIO22, SCL接GPIO21
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  // pwm.setPWMFreq(1);
  // pwm.setPWM(18, 2048, 0);
  // pwm.setPWM(19, 2048, 0);
  // pwm.setPWM(20, 2048, 0);
  // pwm.setPWM(21, 2048, 0);
  // pwm.setPWM(22, 2048, 0);
}
void PCA9685() {
    pwm.setPWM(18, 4096, 0);       // turns pin fully on
    delay(1000);
    pwm.setPWM(18, 0, 4096);  
  
}