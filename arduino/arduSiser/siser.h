#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "siserconfig.h"

struct myDht_t {
  float t;
  float h;
};

struct myGps_t {
  float la; // latitude
  float lo; // longitude
};

struct siser_t {
  uint16_t gasppm; // 0-1000 ppm
  byte rain;     // 0-100%
  myDht_t dht;
  myGps_t gps;
  float lx;
};

struct siserCompleteDataframe_t {
  char Init[4];
  siser_t s;
  char End[4];
};

int dataframeToString(siser_t *s, char *buf){
  String temp = String(s->dht.t);
  String humi = String(s->dht.h);
  String la = String(s->gps.la);
  String lo = String(s->gps.lo);
  return sprintf(buf,
    "gasppm: %d\n"
    "rain: %d\n"
    "dht: {t:%s, h:%s}\n"
    "gps: {la:%s, lo:%s}\n"
    "lx: %d\n\n",
    s->gasppm,
    s->rain,
    temp.c_str(), humi.c_str(),
    la.c_str(), lo.c_str(),
    s->lx
  );
}

#ifdef DEBUG
siser_t sEx = { // siser Example
  1000, // gasppm
  15,   // rain
  {23.5,51}, //dht:t,h
  {-12.0966515,-77.0306064}, // gps:la,lo
  55   // lx
};
#endif
