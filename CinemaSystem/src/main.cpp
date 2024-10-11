#include <Arduino.h>

#include "startup.h"
#include "receiver.h"
#include "commandHandler.h"

void setup() {
  InitializeSerial();
  setupIrReceiver();
  InitializePins();
}

void loop() {
  int command = checkForData();
  if(command != -1){
    handle(command);
  }

  delay(1);
}
