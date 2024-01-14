#include "temperature_DS18B20.h"

// TEMPERATURE
#define ONE_WIRE_BUS D4
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


std::array<float, 2> initializeTemperatureSensor(){
  sensors.begin();
  std::array<float, 2> result = getTempWithErrorResistance();
  float temp = result[0];
  float timeSpentToGetTemp = result[1] / 1000;
  
  Serial.println("Temperature sensor is ready! Got the correct result in: " + String(timeSpentToGetTemp) + " seconds. Temp is: " + String(temp, 3));

  return result;
}

// The temp sensor is probably having some mechanical problems. This band aids it.
std::array<float, 2> getTempWithErrorResistance(void)
{
  std::array<float, 2> result = {0.0, 0};
  float temp = getTemp();
  if (isTempIsNotBugged(temp))
  {
    Serial.println("Temp is ok, not bugged. Temp:" + String(temp, 3));
    result[0] = temp;
    return result;
  }

  Serial.println("Temp is bugged!");
  long fiveMins = oneMinute*5;
  for (long i = oneSecond; i <= fiveMins; i += oneSecond)
  {
    Serial.println("Error resistance has been triggered. Delay for " + String(i / oneSecond) + " seconds");

    blinkWhileDelaying(i, 300);

    temp = getTemp();
    result[0] = temp;
    result[1] += i;

    if (isTempIsNotBugged(temp))
    {
      Serial.println("Error resolved, correct temp is: " + String(temp, 3));
      return result;
    }
  }

  Serial.println("Error still continues: " + String(temp, 3));
  return result;
}

bool isTempIsNotBugged(float temp)
{
  return temp > -4 && temp < 50;
}

float getTemp(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  float temp = sensors.getTempCByIndex(0);
  Serial.println("Temp: " + String(temp, 3));

  return temp;
}