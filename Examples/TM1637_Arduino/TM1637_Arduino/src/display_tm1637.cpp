#include "display_tm1637.h"

// DISPLAY
int CLK = 3;
int DIO = 4;
TM1637 tm(CLK,DIO);
// 1 2 3 4 5 6 7 8 9 10(a) 11(b) 12(c) 13(d) 14(e) 15(f)

void initializeDisplayTm1637(){
  // Initialize Display
  int aa = 10;
  tm.set(5);
  tm.point(1);
  tm.display(0, aa);
  tm.display(1, aa);
  tm.display(2, aa);
  tm.display(3, aa);
}

bool isTempIsNotBugged(float temp)
{
  return temp > -4 && temp < 50;
}

void displayTemperatures(int currentTemp, int prevTemp)
{
  int ff = 15;  

  if (isTempIsNotBugged(prevTemp))
  {
    tm.display(0, prevTemp / 10 % 10);
    tm.display(1, prevTemp % 10);
  } else {
    tm.display(0, ff);
    tm.display(1, ff);
  }

  if (isTempIsNotBugged(currentTemp))
  {
    tm.display(2, currentTemp / 10 % 10);
    tm.display(3, currentTemp % 10);
  } else {
    tm.display(2, ff);
    tm.display(3, ff);
  }
}