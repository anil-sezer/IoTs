#include <ESP8266HTTPClient.h>

String SendGetRequest(WiFiClient client, String apiEndpoint);
String SendPostRequest(WiFiClient client, String apiEndpoint, String body);