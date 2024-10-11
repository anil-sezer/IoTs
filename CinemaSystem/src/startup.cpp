#include "startup.h"


void InitializeSerial() {
      Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\n"));
}
