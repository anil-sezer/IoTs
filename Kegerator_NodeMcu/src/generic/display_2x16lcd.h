#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void initializeDisplay16x2Lcd();
void displayTemperatures(float currentTemp, int minTemp, int maxTemp);
void displayText(String text);