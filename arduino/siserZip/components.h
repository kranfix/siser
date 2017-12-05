#include <Arduino.h>
#include <Wire.h>

extern byte buff[2];

// lx
void BH1750_Init(int address);
byte BH1750_Read(int address);

// xbee
boolean xbeeLisening();
