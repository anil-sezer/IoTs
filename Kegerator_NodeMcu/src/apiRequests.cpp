#include "apiRequests.h"

String SendGetRequest(WiFiClient client, String apiEndpoint){
  Serial.println("EET: " + apiEndpoint);

    HTTPClient http;
    http.begin(client, apiEndpoint);
    http.addHeader("Content-Type", "application/json");
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
      http.end();
      return response;
    }

    Serial.print("Error on sending GET: ");
    Serial.println(httpResponseCode);
    http.end();
    return "";
}


String SendPostRequest(WiFiClient client, String apiEndpoint, String body){
  Serial.println("POST: " + apiEndpoint);
  Serial.println("Body: " + body);

  HTTPClient http;
  http.begin(client, apiEndpoint);
  http.addHeader("Content-Type", "application/json");
  
  int httpResponseCode = http.POST(body);
  
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
    http.end();
    return response;
  }

  Serial.print("Error on sending POST: ");
  Serial.println(httpResponseCode);
  http.end();
  return "";
}