#include <OneWire.h>
#include <DallasTemperature.h>
#include "blink.h"

float getTemp(void);
bool isTempIsNotBugged(float temp);
std::array<float, 2> getTempWithErrorResistance(void);
std::array<float, 2> initializeTemperatureSensor();

extern DallasTemperature sensors;