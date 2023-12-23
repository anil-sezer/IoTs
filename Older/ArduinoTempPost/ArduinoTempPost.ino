#include "Ethernet.h"
#include "SPI.h"

//Temp
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
//Temp

// Ethernet
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;
long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 3000; // READING INTERVAL
float p = 0.00;
String data;
// Ethernet

void setup() {
  sensors.begin();  // Start up the library
  Serial.begin(9600);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); 
  }
  
  Serial.println("Ready after a bit");
  delay(10000); // GIVE THE SENSOR SOME TIME TO START
}

void loop(){

  sensors.requestTemperatures();
  p = sensors.getTempCByIndex(0);
  
  data = "temp=";
  data = data + p;
  
  
  if (client.connect("192.168.1.105",1880)) { // REPLACE WITH YOUR SERVER ADDRESS
    
    Serial.println("loop");
    
    client.println("POST /update-sensor HTTP/1.1"); // HTTP POST TO /results
    client.println("Host: http://raspberrypi.local:1880/"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); // DATA TYPE
    client.print("Content-Length: ");  
    client.println(data.length()); 
    client.println();
    client.print(data);
  }
  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }
  delay(300000); // 5 MINS DELAY
}
