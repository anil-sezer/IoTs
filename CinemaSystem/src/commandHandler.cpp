#include "commandHandler.h"

const int shutDownCommand = 0x46; // Square button, at below of the remote
const int bootCommand = 0x47; // Play button, at below of the remote

const int volumeUp = 0x7; // Primary Volume up button, at middle of the remote
const int volumeDown = 0xB; // Primary Volume down button, at middle of the remote

const int speakerBootAndShutdownPin = 5;
const int volumeUpPin = 6;
const int volumeDownPin = 7;
const int pcBootAndShutdownPin = 4;

bool isSystemIsUp = false;

void bootUp();
void shutdown();
void volumeControl(int pin);
void simulateButtonPress(int pin);

void InitializePins(){
    pinMode(speakerBootAndShutdownPin, OUTPUT);
    digitalWrite(speakerBootAndShutdownPin, LOW);

    pinMode(volumeUpPin, OUTPUT);
    digitalWrite(volumeUpPin, LOW);

    pinMode(volumeDownPin, OUTPUT);
    digitalWrite(volumeDownPin, LOW);
}

void handle(int command) {
    switch (command) {
        case bootCommand:
            bootUp();
            break;
        case shutDownCommand:
            shutdown();
            break;
        case volumeUp:  
            volumeControl(volumeUpPin);
            break;
        case volumeDown:
            volumeControl(volumeDownPin);
            break;
        default:
        Serial.println("Unknown command. Skipping.");
        break;
  }
    Serial.println();
}

void shutdown(){
    Serial.println("Received command: shutdown");

    if(isSystemIsUp == false){
        Serial.println("System is already down. Ignoring shutdown command");
        return;
    }

    simulateButtonPress(speakerBootAndShutdownPin);
    simulateButtonPress(pcBootAndShutdownPin);
    isSystemIsUp = false;
    Serial.println("Shutdown complete.");
}

void bootUp(){
    Serial.println("Received command: bootUp");

    if(isSystemIsUp == true){
        Serial.println("System is already up. Ignoring bootUp command");
        return;
    }

    simulateButtonPress(speakerBootAndShutdownPin);
    Serial.println("Waiting 3 seconds for speaker to boot up");
    delay(3000);

    for(int i = 1; i <= 5; i++) {
        simulateButtonPress(volumeUpPin);
    }

    delay(7000);
    Serial.println("Wait addiotional 7 seconds for speaker to boot up");
    simulateButtonPress(pcBootAndShutdownPin);

    isSystemIsUp = true;

    Serial.println("Boot up complete.");
}

void volumeControl(int pin){
    Serial.println("Received command: volume up or down");

    if(isSystemIsUp == false){
        Serial.println("System is down. Ignoring volume command");
        return;
    }

    simulateButtonPress(pin);
}

void simulateButtonPress(int pin){
    delay(50);
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
    Serial.print("Simulated press for pin ");
    Serial.println(pin);
}
