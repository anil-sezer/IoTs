#include "relaySingleChannel.h"

// Only used 1 channel
uint8_t relayPin;

void initializeRelay(uint8_t pin){
    relayPin = pin;
    int oneSecond = 1000;
    
    pinMode(relayPin, OUTPUT);
    // digitalWrite(relayPin, HIGH);

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

// todo-anil-beforeMerge: Format this file to support 2 channel relays with ease of use
int relayStatus(){
    return digitalRead(relayPin);
}