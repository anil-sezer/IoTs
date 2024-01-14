#include "KegeratorsDirectiveDto.h"

const String Init = "INITIALIZE";

KegeratorsDirectiveDto::KegeratorsDirectiveDto(String json) {
    if(json == Init){
        return;
    }

    // Deserialize the JSON document
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);

    // Example Json:
    // {"MinTemp":20,"MaxTemp":23,"ReportInterval":60000,"TempCheckInterval":5000,"CooldownPeriod":600000}
    // Extract values
    minTemp = doc["MinTemp"];
    maxTemp = doc["MaxTemp"];
    reportInterval = doc["ReportInterval"];
    tempCheckInterval = doc["TempCheckInterval"];
    cooldownPeriod = doc["CooldownPeriod"];
}

void KegeratorsDirectiveDto::displayData() {
    Serial.println("minTemp: " + String(minTemp));
    Serial.println("maxTemp: " + String(maxTemp));
    Serial.println("minTemp: " + String(reportInterval));
    Serial.println("maxTemp: " + String(tempCheckInterval));
    Serial.println("maxTemp: " + String(cooldownPeriod));
}
