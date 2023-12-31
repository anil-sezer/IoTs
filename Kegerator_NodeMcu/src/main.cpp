#include <Arduino.h>

#include "temperature_DS18B20.h"
#include "relayTwoChannel.h"
#include "genericGlobals.h"
#include "display_tm1637.h"
#include "apiRequests.h"
#include "blink.h"
#include "wifi.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* apiEndpoint = API_ENDPOINT;

KegeratorsDirective getDirectives();


void setup() {
    Serial.begin(115200);
    Serial.println("Ready to roll!\n****************************************");

    InitializeInternalLed();
    initializeDisplayTm1637();
    initializeTemperatureSensor();
    connectToWifi(ssid, password);
    initializeRelay();

    Serial.println("Init done.");
}

void loop() {
    int temp1 = getTemp();
    int temp2 = 30;
    Serial.println("Temp 1: " + String(temp1));
    Serial.println("Temp 2: " + String(temp2));
    displayTemperatures(temp1, temp2);


    delay(oneSecond * 4);
    
}

KegeratorsDirective getDirectives(){
    String result = SendGetRequest(client, apiEndpoint);

    return KegeratorsDirective(result);
}

class KegeratorsDirective {
  public:
    int minTemp;
    int maxTemp;
    int reportInterval; // As seconds? Maybe mins?
    int tempCheckInterval; // As seconds? Maybe mins?

    // Constructor
    KegeratorsDirective(String json) {

    }

    // For debug
    void displayData() {
      Serial.println("minTemp: " + String(minTemp));
      Serial.println("maxTemp: " + String(maxTemp));
    }
};