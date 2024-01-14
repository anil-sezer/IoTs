#include <Arduino.h>
#include "blink.h"


void setup() {
  Serial.begin(115200);
  Serial.println("Ready to roll!\n****************************************");

  InitializeInternalLed();
}

void loop() {
  blinkWhileDelaying(1000, 500);
}