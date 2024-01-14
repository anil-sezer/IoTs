#include "DHT11_Temperature_NodeMcuV3.h"

void setup() {
  Serial.begin(115200);
  initializeTemperatureAndMoistureSensor();
  pinMode(D8, OUTPUT);
}

void loop() {
  // Delay between measurements.
  delay(sensorMinimumDelay);
  getTempAndHumidity();
}