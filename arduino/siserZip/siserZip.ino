#include "config.h"
#include <DHT.h>
#include <TinyGPS.h>
#include "siser.h"
#include "components.h"
#include "solarTracker.h"

const unsigned long daymillis = 24 * 3600 * 1000;

HardwareSerial Serial1(2);

TinyGPS gps;
DHT dht(DHTPIN, DHTTYPE);

unsigned long now, lastDebug, lastGps, lastSolarTracker;

solarTracker_t st = {
  { // servo Pin
    18, // Azimut servo pin
    19  // Polar servo pin
  },
  { // servo channels
    1, // Channel for azimut servo
    2  // Channel for polar servo
  },
  { // LDR Pin
   32, // Top-left LDR pin
   33, // Top-Right LDR Pin
   2,  // Down-left LDR pin
   4   // Down-Right LDR Pin
  }
};

siserCompleteDataframe_t sCDt = {
  {'O','P','E','N'},
  sEx,
  {'C','H','A','U'}
};
byte sCDtLen = sizeof(sCDt);

void setup() {
  xbeeSerial.begin(9600);

  //gpsSerial.begin(9600);
  Wire.begin();
  BH1750_Init(BH1750_address);
  pinMode(mq2Pin, INPUT);
  pinMode(rainPin, INPUT);
  dht.begin();

  solarTracker_begin(&st);
  lastSolarTracker = millis();

  lastDebug = millis();
  //readGps();

  lastGps = millis();
}

void loop() {
  now = millis();
  if (now - lastDebug >= 2000){
    readSensors();
    /*char buf[128];
    size_t n = dataframeToString(&(sCDt.s),&buf[0]);
    Serial.write((byte*)buf,n);*/
    lastDebug = now;
  }

  if(xbeeLisening()){
    xbeeSerial.write((byte*)&sCDt,sCDtLen);
  }

  /*now = millis();
  if (now - lastGps >= daymillis){
    readGps();
    lastGps = now;
  }*/

  now = millis();
  if (now - lastSolarTracker >= 100){
    solarTracker_loop(&st);
    lastSolarTracker = now;
  }
}

void readSensors() {
#ifndef DEBUG
  // Lectura de nivel de gas
  sCDt.s.gasppm = analogRead(mq2Pin) >> 2;

  // Lectura de nidel de lluvia
  int Nivel_lluvia = analogRead(rainPin) >> 2;
  sCDt.s.rain = map(Nivel_lluvia, 1023, 460, 0, 100);

  // Lectura del DHT22: Temperatura y Humedad
  sCDt.s.dht.t = dht.readTemperature();
  sCDt.s.dht.h = dht.readHumidity();

  // Lectura de lumenes
  if (BH1750_Read(BH1750_address) == 2) {
    sCDt.s.lx = (((uint16_t)(buff[0]) << 8) | buff[1]) * 0.54;
  }
#endif
}

void readGps(){
#ifndef DEBUG
  // Lectura del GPS
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (gpsSerial.available()) {
      char c = gpsSerial.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)){ // Did a new valid sentence come in?
        newData = true;
      }
    }
  }

  if (newData){
    unsigned long age;
    gps.f_get_position(&(sCDt.s.gps.la), &(sCDt.s.gps.lo), &age);
  }
#endif
}
