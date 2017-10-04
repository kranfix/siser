#include "siserconfig.h"
#include <Wire.h>
#include "DHT.h"
#include <TinyGPS.h>
#include "siser.h"
TinyGPS gps;

DHT dht(DHTPIN, DHTTYPE);

siserCompleteDataframe_t sCDt = {"OPEN",siser_t{},"CHAU"};
byte sCDtLen = sizeof(sCDt);

int Nivel_lluvia;
int triger = 9;
int echo = 8;
int tiempo;
int distancia;
int BH1750_address = 0x23;
byte buff[2];

SiserStatus sStatus = SISER_SiserReadyToTx;

void setup() {
  Wire.begin();
  BH1750_Init(BH1750_address);
  Serial.begin(9600);
  pinMode(mq2Pin, INPUT);
  pinMode(rainPin, INPUT);
  pinMode(triger, OUTPUT);
  pinMode(echo, INPUT);
  dht.begin();
  Serial1.begin(9600);
}

void loop() {
  readLightweightSensors();
  readHeavyweightSensors();
  /*if (sStatus == SISER_SiserReadyToTx) {
    Serial.write(sStatus);
    if (Serial.available()) {
      SiserStatus rStatus = (SiserStatus)Serial.read();
      if (rStatus == SISER_RpiReadyToRx) {
        sStatus = rStatus;
      }
    } else{
      delay(1500);
    }
  } else if (sStatus == SISER_RpiReadyToRx) {
    Serial.write((byte*)&s, sizeof(s));
    if(Serial.available() {
      
    }
  }*/
  sCDt.s = s;
  Serial.write((byte*)&sCDt,sCDtLen);
  delay(1500);
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
  Nivel_lluvia = analogRead(rainPin);
  sCDt.s.rain = map(Nivel_lluvia, 1023, 460, 0, 100);

  // Lectura de distancia
  /*digitalWrite(triger, LOW);     delayMicroseconds(2);
  digitalWrite(triger, HIGH);    delayMicroseconds(10);
  digitalWrite(triger, LOW);
  tiempo = pulseIn(echo, HIGH); //distancia=340*tiempo/2 convertimos a las unidades correctas
  distancia = (tiempo / 2) / 29.1; //distancia = velocidad*tiempo en cm
  */
  
  // Lectura del DHT22: Temperatura y Humedad
  sCDt.s.dht.h = dht.readHumidity();
  sCDt.s.dht.t = dht.readTemperature();

  // Lectura de lumenes
  if (BH1750_Read(BH1750_address) == 2) {
    sCDts.lx = ((buff[0] << 8) | buff[1]) / 1.2;
  }
}

void readHeavyweightSensors(){
  // Lectura del GPS
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (Serial1.available()) {
      char c = Serial1.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    unsigned long age;
    gps.f_get_position(&sCDt.s.gps.la, &sCDt.s.gps.lo, &age);
  }
}
