#include "wifi.h"
#include "blink.h"
#include "genericGlobals.h"

WiFiClient client;

void connectToWifi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  Serial.println("Attempting to connect to WiFi network...");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) { // Try to connect for a certain number of attempts
    blinkWhileDelaying(oneSecond, 300);
    Serial.print("Connecting to WiFi...");
    Serial.print("Attempt ");
    Serial.print(attempts + 1);
    Serial.print(" of 20. Status: ");
    Serial.println(wlStatusToString(WiFi.status()));
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("Failed to connect to WiFi.");
    Serial.println("Credentials: ");
    Serial.println("SSID: " + String(ssid));
    Serial.println("Password: " + String(password));
    Serial.println(" Check your credentials and try again.");
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