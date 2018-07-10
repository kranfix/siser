#ifndef SISER_H
#define SISER_H

#include "config.h"

struct myDht_t { float t, h; };
struct myAcc_t { float x, y, z; };
struct myCurrent_t { float ol, cl; };

struct myInd_t {
  uint8_t d; // duty
  float v; // Vind: Induction voltage
};

struct siser_t {
  uint8_t id;
  uint8_t rain;  // 0-100%
  uint8_t uv;
  myDht_t dht;
  float bat;     // battery: 0-5V
  myAcc_t acc;   // accelerometer
  myCurrent_t curr; // Current sensors
  myInd_t ind;
};

static siser_t siser = { // siser Example
  ID,        // id: 0 - 255
  15,        // rain
  0,         // UV
  {23.5,51}, // dht:t,h
  50.0,      // Battery voltage
  {0.1,0.2,-9.07}, // Accelerometer: x, y, z
  {2.0,2.0},  // Current
  {0.0, 0.0}  // Induction: duty, voltage
};

#endif
