#include <TM1637.h>
#include <Arduino.h>

#include "temperature_DS18B20.h"

void initializeDisplayTm1637();
bool isTempIsNotBugged(float temp);
void displayTemperatures(int currentTemp, int prevTemp);