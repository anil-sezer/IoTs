#include <Arduino.h>

extern const int shutDownCommand;
extern const int bootCommand;

extern const int volumeUp;
extern const int volumeDown;

void InitializePins();
void handle(int command);