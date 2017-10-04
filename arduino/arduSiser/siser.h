#include <inttypes.h>

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

