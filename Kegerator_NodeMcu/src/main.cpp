#include <Arduino.h>

#include "temperature_DHT11.h"
#include "dto/KegeratorsDirectiveDto.h"
#include "relayTwoChannel.h"
#include "display_2x16lcd.h"
#include "genericGlobals.h"
#include "apiRequests.h"
#include "blink.h"
#include "wifi.h"

KegeratorsDirectiveDto getDirectives();
bool FridgeControls(float temp, KegeratorsDirectiveDto directives, float timeSpentToGetTemp);
bool compressorOverheatingFailsafeTrigger(float timeSpentToGetTemp);
void sendReport(float temp, bool isFridgeIsOn);
void handleFridgeCooldownTimer(long timeAsMiliseconds);

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* apiRoot = API_ENDPOINT;
const char* apiDirectivesEndpoint = "/GetIotDirectives";
const char* apiReportEndpoint = "/StoreDevicesReport";

long consecutiveWorkingTimeOfTheFridge = 0;
long timeSinceLastTempCheck = 0;
long timeSinceLastReport = 0;
long remainingCooldownTime = 0;
bool isFridgeIsOn = false;
long cooldownPeriod = oneMinute * 2;
KegeratorsDirectiveDto directives = KegeratorsDirectiveDto(Init);

float temp = -1;
float humidity = -1;

void setup() {
    Serial.begin(115200);
    Serial.println("Ready to roll!\n****************************************");

    InitializeInternalLed();
    initializeRelay(D8);
    initializeTemperatureAndMoistureSensor();
    delay(sensorMinimumDelay);
    std::array<float, 2> result = getTempAndHumidity();
    temp = result[0];
    humidity = result[1];

    connectToWifi(ssid, password);
    directives = getDirectives();
    // initializeDisplay16x2Lcd(); // Open up later
    Serial.println("Init done.");
}

void loop() {
  Serial.println("Loop started");
  blinkWhileDelaying(oneSecond, oneSecond / 2);

  if(timeSinceLastTempCheck > directives.tempCheckInterval){
    std::array<float, 2> result = getTempAndHumidity();
    temp = result[0];
    humidity = result[1];

    timeSinceLastTempCheck = 0;

    // displayTemperatures(temp, directives.minTemp, directives.maxTemp);
    // isFridgeIsOn = FridgeControls(temp, directives, timeSpentToGetTemp);
    isFridgeIsOn = FridgeControls(temp, directives, 0);
  } else {
    Serial.println("Will check the temp ~" + String((directives.tempCheckInterval - timeSinceLastTempCheck) / 1000) + " seconds later");
  }


  if(timeSinceLastReport > directives.reportInterval){
    sendReport(temp, isFridgeIsOn);
    directives = getDirectives();
    timeSinceLastReport = 0;
  } else {
    Serial.println("Will report ~" + String((directives.reportInterval - timeSinceLastReport) / 1000) + " seconds later");
  }

  blinkWhileDelaying(oneSecond * 4, oneSecond * 2);
  timeSinceLastReport += oneSecond * 4;
  timeSinceLastTempCheck += oneSecond * 4;
  handleFridgeCooldownTimer(oneSecond * 4 * -1);
}

void handleFridgeCooldownTimer(long timeAsMiliseconds){
  if(remainingCooldownTime == 0){
    return;
  }

  remainingCooldownTime += timeAsMiliseconds;

  if (remainingCooldownTime < 0)
  {
    remainingCooldownTime = 0;
  }
}

KegeratorsDirectiveDto getDirectives() {
    String endpointWithParams = apiRoot;
    endpointWithParams.concat(apiDirectivesEndpoint);
    endpointWithParams.concat("?deviceName=Kegerator");
    String json = SendGetRequest(client, endpointWithParams);

    return KegeratorsDirectiveDto(json);
}

void sendReport(float temp, bool isFridgeIsOn) {
    String endpoint = apiRoot;
    endpoint.concat(apiReportEndpoint);

    String tempAsString = String(temp, 3);
    String isFridgeIsOnAsString = isFridgeIsOn ? "true" : "false";

    // String body = "{\"temp\":";
    // body.concat(temp);
    // body.concat(",\"");
    // body.concat("isFridgeIsOn\":");
    // body.concat(isFridgeIsOn);
    // body.concat("}");

    // EXAMPLE: 
    // {
    //   "DeviceName": "Kegerator",
    //   "Report": {
    //     "Temp": 17.5,
    //     "IsFridgeIsOn": true
    //   }
    // }
    String body = "{\"DeviceName\": \"Kegerator\",\"Report\": {\"Temp\":" + tempAsString + ",\"IsFridgeIsOn\":" + isFridgeIsOnAsString + "} }";

    String result = SendPostRequest(client, endpoint, body);
    Serial.println(result);
}

bool FridgeControls(float temp, KegeratorsDirectiveDto directives, float timeSpentToGetTemp)
{
  // if(compressorOverheatingFailsafeTrigger(timeSpentToGetTemp)){
  //   return false;
  // }

  if (temp > directives.minTemp && temp < directives.maxTemp)
  {
    Serial.println("Temperature is in the ideal range, SUSPEND. Temp: " + String(temp, 3));
    consecutiveWorkingTimeOfTheFridge = 0;
    relayOff();
    return false;
  }
  else if (temp > 0 && temp < directives.minTemp)
  {
    Serial.println("Temperature is low, SUSPEND. Temp: " + String(temp, 3));
    consecutiveWorkingTimeOfTheFridge = 0;
    relayOff();
    return false;
  }
  else if (temp > directives.maxTemp)
  {
    Serial.println("Temperature is too high, START. Temp: " + String(temp, 3));
    relayOn();
    return true;
  }

  Serial.println("Bug! Code should have never reached here. " + String(temp, 3));
  // displayText("BUG!!");
  relayOff();
  return false;
}

// Fridge is old, I don't want to work it too hard.
bool compressorOverheatingFailsafeTrigger(float timeSpentToGetTemp)
{
  handleFridgeCooldownTimer(timeSpentToGetTemp);

  if (relayStatus() == HIGH && !isFridgeIsOn)
  {
    consecutiveWorkingTimeOfTheFridge = 0;
    return false;
  }

  consecutiveWorkingTimeOfTheFridge = consecutiveWorkingTimeOfTheFridge + timeSpentToGetTemp;

  const long workingTimeBeforeCooldown = oneMinute * 10;
  if (consecutiveWorkingTimeOfTheFridge < workingTimeBeforeCooldown)
  {
    return false;
  }
  remainingCooldownTime = 0; // bug!
  
  Serial.print("Compressor needs to cool down for " + String(cooldownPeriod/oneMinute) + " minutes... ");
  relayOff();

  displayText("Cooldown");

  consecutiveWorkingTimeOfTheFridge = 0;


  String cooldownEndMsg = "Cooldown complete!";
  Serial.println(cooldownEndMsg);
  displayText(cooldownEndMsg);
  return true;
}
