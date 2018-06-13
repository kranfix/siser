#include "config.h"
#include <DHT.h>
#include "sleep.h"
#include <RTClibExtended.h>
#include <EEPROM.h>
#include "utils.h"
#include "siser.h"
#include <didiusJsonIdl.h>

RTC_DS3231 RTC;

DHT dht(DHTPIN, DHTTYPE);

char buf[150];
DataFrame dt(buf,TYPE,ID);

void setup() {
  Serial.begin(9600);

  pinMode(rainPin, INPUT);
  pinMode(sensorPowerPin,OUTPUT);
  pinMode(xbeePowerPin,OUTPUT);
  dht.begin();

  //Wire.begin();
  RTC.begin();
#ifdef CLEAREEPROM
  Serial.println("Iniciando borrado de ");
  for (int i = 0 ; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  delay(100);
  Serial.println("Limpiado de EEPROM terminado.");
  Serial.println("Reprogramar sin la constante CLEAREEPROM");
  for(;;);
#else
  if(EEPROM.read(RtcSetDir) == 0){
    RTC.adjust(DateTime(__DATE__, __TIME__));
    EEPROM.write(RtcSetDir, 1);
  }
#endif
  
  //clear any pending alarms
  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, false);
  RTC.armAlarm(2, false);
  RTC.clearAlarm(2);
  RTC.alarmInterrupt(2, false);

  //Set SQW pin to OFF (in my case it was set by default to 1Hz)
  //The output of the DS3231 INT pin is connected to this pin
  //It must be connected to arduino D2 pin for wake-up
  RTC.writeSqwPinMode(DS3231_OFF);

  RTC.setAlarm(wakeUpFreq, ss1, mm1, hh1, 0);   //set your wake-up time here
  RTC.alarmInterrupt(1, true);

  setupWakeUp();
}

void loop() {
  digitalWrite(sensorPowerPin,HIGH);
  digitalWrite(xbeePowerPin,HIGH);
  delay(1000); // delay for restablish the meassures

  dt.reset();
  readSimpleSensors();
  dt.close();
  Serial.write(buf,dt.len());
  delay(500);
  digitalWrite(sensorPowerPin,LOW);
  digitalWrite(xbeePowerPin,LOW);
  delay(500);
  sleepNow();

  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, true);
}

void readSimpleSensors() {
#ifndef DEBUG
  // Rain level meassure
  int rainLevel = averageAnalogRead(rainPin,8);
  siser.rain = mapfloat(rainLevel, 1023, 250, 0, 100);

  int uvLevel = averageAnalogRead(rainPin,8);
  siser.uv = mapfloat(uvLevel, 200, 568, 0.0, 15.0);

  // Lectura del DHT22: Temperatura y Humedad
  siser.dht.t = dht.readTemperature();
  siser.dht.h = dht.readHumidity();

  // Battery level (Volt)
  siser.bat = averageAnalogRead(batPin,8) * V5 / 1024;
#endif
  dt.addInt("rain",siser.rain);
  dt.addFloat("uv",siser.uv);
  dt.Dht(siser.dht.t,siser.dht.h);
  dt.addFloat("bat",siser.bat);
}
