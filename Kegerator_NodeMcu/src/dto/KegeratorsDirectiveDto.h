#ifndef KegeratorsDirectiveDto_h
#define KegeratorsDirectiveDto_h

#include <Arduino.h>
#include <ArduinoJson.h>

extern const String Init;

class KegeratorsDirectiveDto {
  public:
    int minTemp;
    int maxTemp;
    // Miliseconds
    long reportInterval;
    long tempCheckInterval;
    long cooldownPeriod;

    // Constructor
    KegeratorsDirectiveDto(String json);

    // For debug
    void displayData();
};

#endif
