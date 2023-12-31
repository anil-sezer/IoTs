#include <OneWire.h>
#include <DallasTemperature.h>
#include "blink.h"

float getTemp(void);
bool isTempIsNotBugged(float temp);
float errorResistance(float temp);
void initializeTemperatureSensor();

extern DallasTemperature sensors;