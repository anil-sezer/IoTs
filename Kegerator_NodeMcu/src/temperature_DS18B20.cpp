#include "temperature_DS18B20.h"
#include "genericGlobals.h"

// TEMPERATURE
#define ONE_WIRE_BUS D2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


void initializeTemperatureSensor(){
  sensors.begin();
}

// The temp sensor is probably having some mechanical problems. This band aids it.
float errorResistance(float temp)
{
  if (isTempIsNotBugged(temp))
  {
    Serial.println("Temp is ok, not bugged.");
    return temp;
  }

  Serial.println("Temp is bugged!");
  long tenSecs = oneSecond*10;
  long fiveMins = oneMinute*5;
  for (long i = tenSecs; i <= fiveMins; i += tenSecs)
  {
    Serial.println("Error resistance has been triggered. Delay for " + String(i / oneSecond) + " seconds");

    blinkWhileDelaying(i, 300);

    temp = getTemp();

    if (isTempIsNotBugged(temp))
    {
      Serial.println("Error resolved, correct temp is: " + String(temp, 3));
      return temp;
    }
  }

  Serial.println("Error still continues: " + String(temp, 3));
  return temp;
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