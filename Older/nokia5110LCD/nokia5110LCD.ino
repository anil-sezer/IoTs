#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Declare LCD object for software SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

int rotatetext = 1;

void setup()   {
  Serial.begin(9600);

  //Initialize Display
  display.begin();

  // you can change the contrast around to adapt the display for the best viewing!
  display.setContrast(100);

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Hello world!");
  display.display();
  delay(12000);
  //display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:

}
