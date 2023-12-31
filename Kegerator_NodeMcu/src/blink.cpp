#include "blink.h"

void InitializeInternalLed(){
  pinMode(LED_BUILTIN, OUTPUT);
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