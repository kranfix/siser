#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

struct myDht_t {
  float t;
  float h;
};

struct siser_t {
  uint8_t id;
  uint8_t rain;  // 0-100%
  myDht_t dht;
  float bat;     // battery: 0-5V
};

int dataframeToString(siser_t *s, char *buf){
  String batV = String(s->bat);
  String temp = String(s->dht.t);
  String humi = String(s->dht.h);
  return sprintf(buf,
    "{\"type\":\""   TYPE   "\","
    "\"id\": %d,"
    "\"rain\": %d,"
    "\"dht\": {\"t\":%s, \"h\":%s},"
    "\"bat\": %s}"
    "\n",
    s->id,
    s->rain,
    temp.c_str(), humi.c_str(),
    batV.c_str()
  );
}

siser_t siser = { // siser Example
  ID,        // id: 0 - 255
  15,        // rain
  {23.5,51}, // dht:t,h
  50.0       // Battery voltage
};
