#include "siserconfig.h"
#include <Wire.h>
#include <DHT.h>
#include <TinyGPS.h>
#include "siser.h"
TinyGPS gps;

DHT dht(DHTPIN, DHTTYPE);

siserCompleteDataframe_t sCDt = {"OPEN",siser_t{},"CHAU"};
byte sCDtLen = sizeof(sCDt);

int triger = 9;
int echo = 8;
int tiempo;
int distancia;
int BH1750_address = 0x23;
byte buff[2];

void setup() {
  Wire.begin();
  BH1750_Init(BH1750_address);
  pinMode(mq2Pin, INPUT);
  pinMode(rainPin, INPUT);
  pinMode(triger, OUTPUT);
  pinMode(echo, INPUT);
  dht.begin();
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  gpsSerial.begin(9600);
  btSerial.begin(9600);
}

void loop() {
  readLightweightSensors();
  readHeavyweightSensors();
  
  char buf[80];
  int n = dataframeToString(&(sCDt.s),buf);
  Serial.write(buf,n);
  xbeeSerial.write((byte*)&sCDt,sCDtLen);
  btSerial.write(buf,n);
  delay(2000);
}

void BH1750_Init(int address) {
  Wire.beginTransmission(address);
  Wire.write(0x10); // 1 [lux] aufloesung
  Wire.endTransmission();
}

byte BH1750_Read(int address) {
  byte i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available()) {
    buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  return i;
}

void readLightweightSensors() {
  // Lectura de nivel de gas
  sCDt.s.gasppm = analogRead(mq2Pin);

  // Lectura de nidel de lluvia
  int Nivel_lluvia = analogRead(rainPin);
  sCDt.s.rain = map(Nivel_lluvia, 1023, 460, 0, 100);

  // Lectura del DHT22: Temperatura y Humedad
  sCDt.s.dht.t = dht.readTemperature();
  sCDt.s.dht.h = dht.readHumidity();

  // Lectura de lumenes
  if (BH1750_Read(BH1750_address) == 2) {
    sCDt.s.lx = ((buff[0] << 8) | buff[1]) / 1.2;
  }
}

void readHeavyweightSensors(){
  // Lectura del GPS
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (gpsSerial.available()) {
      char c = gpsSerial.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    unsigned long age;
    gps.f_get_position(&(sCDt.s.gps.la), &(sCDt.s.gps.lo), &age);
  }
}
