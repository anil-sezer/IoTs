#include <Arduino.h>
#include "relayTwoChannel.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Ready to roll!\n****************************************");

  initializeRelay(5);
}

void loop() {
  delay(2000);
  Serial.println("ON");
  relayOn();
  delay(2000);
  Serial.println("OFF");
  relayOff();
}
