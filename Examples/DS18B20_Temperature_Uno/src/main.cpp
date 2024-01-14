#include <Arduino.h>
#include "temperature_DS18B20.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Ready to roll!\n****************************************");
  initializeTemperatureSensor();
}

void loop() {
    std::array<float, 2> result = getTempWithErrorResistance();
    float temp = result[0];
    float timeSpentToGetTemp = result[1];
    Serial.println(String(temp, 3));
    delay(2000);
}