#include "config.h"

struct myDht_t {
  float t;
  float h;
};

struct myAcc_t {
  float x;
  float y;
  float z;
};

struct siser_t {
  uint8_t id;
  uint8_t rain;  // 0-100%
  float uv;
  myDht_t dht;
  float bat;     // battery: 0-5V
  myAcc_t acc;   // accelerometer
};

siser_t siser = { // siser Example
  ID,        // id: 0 - 255
  15,        // rain
  0.0,       // UV
  {23.5,51}, // dht:t,h
  50.0,      // Battery voltage
  {0.1,0.2,-9.07}
};

