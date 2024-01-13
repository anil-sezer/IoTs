#include <Arduino.h>
#include "relaySingleChannel.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Ready to roll!\n****************************************");

  initializeRelay(4);
}

void loop() {
  delay(2000);
  Serial.println("ON");
  relayOn();
  delay(2000);
  Serial.println("OFF");
  relayOff();
}
