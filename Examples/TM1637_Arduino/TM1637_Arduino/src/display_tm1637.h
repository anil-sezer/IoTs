#include <TM1637.h>
#include <Arduino.h>

void initializeDisplayTm1637();
bool isTempIsNotBugged(float temp);
void displayTemperatures(int currentTemp, int prevTemp);