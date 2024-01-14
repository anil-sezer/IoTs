#include "display_2x16lcd.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initializeDisplay16x2Lcd(){
  lcd.print("Display initializing");
  delay(1000);
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  displayText("READY");
  lcd.print("Display is ready!");
}

void displayText(String text)
{
  return;
    lcd.clear();
    lcd.setCursor(0,0);

    if(text.length() > 16){
      lcd.print(text.substring(0, 16));
      lcd.setCursor(0,1);
      lcd.print(text.substring(16, 32));
    } else {
      lcd.print(text);
    }
}