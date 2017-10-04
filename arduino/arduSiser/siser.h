#include <inttypes.h>
#include <stdio.h>

#define SISER_SiserReadyToTx 'A'
#define SISER_RpiReadyToRx   'B'
#define SISER_
typedef char SiserStatus;


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
  return sprintf(buf,
    "gasppm: %d\n"
    "rain: %d\n"
    "dht: {t:%f, h:%f}\n"
    "gps: {la:%f, lo:%f}\n"
    "lx: %d\n\n",
    s->gasppm,
    s->rain,
    s->dht.t, s->dht.h,
    s->gps.la, s->gps.lo,
    s->lx
  );
}

