#include "setup.h"
#include "loop.h"
#include <Arduino.h>
void setup() {
  Serial.begin(115200);
  blesetup();
  wifisetup();

}

void loop() {
  wifi();
  delay(1000);
}