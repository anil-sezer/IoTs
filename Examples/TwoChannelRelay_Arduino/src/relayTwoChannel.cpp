#include "relayTwoChannel.h"

// Only used 1 channel
uint8_t relayPin;

void initializeRelay(uint8_t pin){
    relayPin = pin;
    int oneSecond = 1000;
    
    pinMode(relayPin, OUTPUT);

    Serial.println("Relay will flip:");
    relayOn();
    delay(oneSecond * 2);
    relayOff();
    Serial.println("Relay ready!");
}

void relayOn(){
    digitalWrite(relayPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
}

void relayOff(){
    digitalWrite(relayPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
}

int relayStatus(){
    return digitalRead(relayPin);
}