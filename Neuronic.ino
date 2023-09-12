#include "setup.h"
#include "loop.h"
#include <Arduino.h>
void setup() {
  // pinMode(23, OUTPUT);
  // digitalWrite(23, LOW);

  Serial.begin(115200);
  // ledSetup();
  // blesetup();
  PCA9635setup();
  // awssetup();
}

void loop() {
  // led();
  // ble();
  PCA9635();
  // aws();
  delay(10);
}