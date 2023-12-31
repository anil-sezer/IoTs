#include "relayTwoChannel.h"

// Only used 1 channel
const int relayPin = D1;

void initializeRelay(){
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH);
}

void relayOn(){
    digitalWrite(relayPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
}

void relayOff(){
    digitalWrite(relayPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
}