#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = WIFI_SSID;
// const char* ssid = "Huff Puff Puff 2.4";
const char* password = WIFI_PASSWORD;
const char* apiEndpoint = API_ENDPOINT;
// const char* apiEndpoint = "http://192.168.1.105:30002/Iot/SunriseAlarmClockCheck";

const int aMinute = 1000 * 60;

const int relayPin = D1;

WiFiClient client;
void blink(int blinkTime);
void connectToWifi();
String wlStatusToString(wl_status_t status);
String SendGetRequest();

void setup() {
  Serial.begin(115200);
  Serial.println("Sunshine!");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  connectToWifi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    delay(10000);
    return;
  }

  String response = SendGetRequest();

  bool isAlarmActive = false, bringTheSun = false;
  if (response == "")
  {
    blink(500);
  } 
  else 
  {
    // Deserialize the JSON document
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);

    // Extract values
    isAlarmActive = doc["IsAlarmActive"];
    bringTheSun = doc["BringTheSun"];
  }

  if (isAlarmActive && bringTheSun) 
  {
    Serial.println("Bring The Sun action triggered!");
    digitalWrite(relayPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  } 
  else 
  {
    Serial.println("Not the time for the sunshine.");
    digitalWrite(relayPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }

  delay(aMinute);
}

String SendGetRequest(){
    blink(500);

    HTTPClient http;
    http.begin(client, apiEndpoint); // Pass a WiFiClient object and specify the URL
    http.addHeader("Content-Type", "application/json"); // Specify content-type header
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response to the request
      Serial.println(httpResponseCode);   // Print return code
      Serial.println(response);           // Print request answer
      return response;

    } else {
      Serial.print("Error on sending GET: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Close connection
    blink(500);
    return "";
}

void blink(int blinkTime) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(blinkTime / 2); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkTime / 2);
}

void connectToWifi() {
  WiFi.begin(ssid, password);
  Serial.println("Attempting to connect to WiFi network...");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) { // Try to connect for a certain number of attempts
    blink(1000);
    Serial.print("Connecting to WiFi...");
    Serial.print("Attempt ");
    Serial.print(attempts + 1);
    Serial.print(" of 20. Status: ");
    Serial.println(wlStatusToString(WiFi.status())); // Print the WiFi connection status
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("Failed to connect to WiFi. Check your credentials and try again.");
  }
}

String wlStatusToString(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD:        return "WL_NO_SHIELD";
    case WL_IDLE_STATUS:      return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL:    return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED:   return "WL_SCAN_COMPLETED";
    case WL_CONNECTED:        return "WL_CONNECTED";
    case WL_CONNECT_FAILED:   return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST:  return "WL_CONNECTION_LOST";
    case WL_WRONG_PASSWORD:   return "WL_WRONG_PASSWORD";
    case WL_DISCONNECTED:     return "WL_DISCONNECTED";
    default:                  return "UNKNOWN";
  }
}