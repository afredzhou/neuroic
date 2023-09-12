#include <Arduino.h>

int pins[] = {34, 35, 26, 27, 4, 16, 17, 5, 18, 19, 2, 21, 22, 23,25 };
int numPins = sizeof(pins) / sizeof(pins[0]);

void ledSetup(){
for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }

}
void led(){


}