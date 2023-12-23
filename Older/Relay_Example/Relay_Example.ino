/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Relay pin is controlled with D8. The active wire is connected to Normally Closed and common
int relay = 8;
volatile byte relayState = LOW;

void setup() {
  // Pin for relay module set as output
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  // PIR motion sensor set as an input
  // Serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {

  digitalWrite(relay, HIGH);
  relayState = LOW;
  Serial.println("OFF");
  delay(3000);

  digitalWrite(relay, LOW);
  relayState = HIGH;
  Serial.println("ON");
  delay(3000);
}
