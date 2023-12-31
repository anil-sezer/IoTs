#include <Arduino.h>
#include <TM1637.h>

#include "display_tm1637.h"

// GENERIC
int oneSecond = 1000;
long oneMinute = 60000;

// Some get temperature function. Returns random temperatures between -10 and 30
int getTemperature()
{
    return static_cast<int8_t >(random(-10, 30));
}

void setup()
{
    // start serial port
    Serial.begin(115200);
    Serial.println("Ready to roll!\n****************************************");

    initializeDisplayTm1637();

    Serial.println("Init done.");
}

void loop()
{
    int temp1 = 20;
    int temp2 = 30;
    Serial.println("Temp 1: " + String(temp1));
    Serial.println("Temp 2: " + String(temp2));
    displayTemperatures(temp1, temp2);
}