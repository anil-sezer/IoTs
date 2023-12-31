#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// https://lastminuteengineers.com/i2c-lcd-arduino-tutorial/
// The first screen I got is at: 0x27

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Cur. Temp: 19.02");
  
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("Tar. Temp: 22.00");
}

void loop() {
}