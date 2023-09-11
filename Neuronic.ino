#include "setup.h"
#include "loop.h"
#include <Arduino.h>
void setup() {
  Serial.begin(115200);
  // blesetup();
  PCA9685setup();
  // awssetup();
}

void loop() {
  // ble();
  PCA9685();
  // aws();
  delay(1000);
}