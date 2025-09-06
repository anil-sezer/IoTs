#include "blink.h"

void InitializeInternalLed(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Internal led ready.");
  blinkWhileDelaying(1000,300);
}

void blinkWhileDelaying(long delayAmount, int blinkFrequency)
{
  for (;delayAmount >= 0;)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(blinkFrequency/2);
    digitalWrite(LED_BUILTIN, LOW);
    delay(blinkFrequency/2);
    delayAmount = delayAmount - blinkFrequency;
  }
}