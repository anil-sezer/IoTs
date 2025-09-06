#include <ESP8266WiFi.h>

void connectToWifi(const char* ssid, const char* password);
String wlStatusToString(wl_status_t status);

extern WiFiClient client;