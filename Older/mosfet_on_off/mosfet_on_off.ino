 /*
 * IRF520 MOSFET Switch module for Arduino
 * Written by Ahmad Shamshiri for Robojax.com
Date modified: Jun 09, 2018 at 18:58 at Ajax, Ontario, Canada
watch video instruction for this code:https://youtu.be/17vqLv508Uw
 */

#define control 8 // pin that controls the MOSFET

void setup() {
  // IRF520 MOSFET Tutorial by Robojax
  pinMode(control,OUTPUT);// define control pin as output
  Serial.begin(9600);

}

void loop() {
  // IRF520 MOSFET Tutorial by Robojax

  digitalWrite(control,HIGH); // turn the MOSFET Switch ON
  delay(2000);// Wait for 2000 ms or 2 second

  digitalWrite(control,LOW); // Turn the MOSFET Switch OFF
  delay(2000);// Wait for 2000 ms or 2 second


}
