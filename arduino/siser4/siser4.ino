#include <Wire.h>
#include "config.h"
#include "sleep.h"
#include <RTClibExtended.h>
#include <EEPROM.h>
#include "project.h"

#include <DHT.h>

char dtBuf[100];
DataFrame dt(dtBuf,TYPE,ID);

#ifndef GY91
RTC_DS3231 RTC;
#else
unsigned long start, now;
#endif

void setup() {
  DHT dht(DHTPIN, DHTTYPE);
  delay(10);
  dht.begin();
  
  // Communication
  pinMode(commPowerPin,OUTPUT);
  delay(100);
  xbee.begin(9600);

  setupSensorsAndActuators();

  //Wire.begin();
#ifndef GY91
  RTC.begin();

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

  pinMode(commPowerPin,OUTPUT);
  digitalWrite(commPowerPin,HIGH);

#else
  start = millis();
#endif

  setupWakeUp();
  controlVind(false);
}

void loop() {
  digitalWrite(simplePowerPin,HIGH);
  digitalWrite(commPowerPin,HIGH);
  delay(500); // delay for restablish the meassures
  dt.reset();
  readSimpleSensors();
  dt.close();
  digitalWrite(simplePowerPin,LOW);
  delay(200);
  xbee.write(dtBuf,dt.len());
  
#ifdef CURRENT
  digitalWrite(complexPowerPin,HIGH);
  delay(500);
  digitalWrite(commPowerPin,LOW);
  
  dt.reset();
  readCurrent();
  dt.addInt("d",siser.ind.d);
  dt.addInt("v",100 * siser.ind.v);
  dt.close();

  digitalWrite(commPowerPin,HIGH);
  delay(500);
  xbee.write(dtBuf,dt.len());
  delay(50);
#endif

/*#ifdef GY91
  digitalWrite(commPowerPin,HIGH);
  digitalWrite(complexPowerPin,HIGH);
  delay(1000);
  dt.reset();
  if(readAcc() | readBmp()){
    dt.close();
    xbee.write(dtBuf,dt.len());
    delay(500);
  }
#endif*/
  digitalWrite(complexPowerPin,LOW);
  delay(500);
  digitalWrite(commPowerPin,LOW);

#ifdef MOTOR
  delay(50);
  digitalWrite(motorPin,HIGH);
  delay(motorTime);
  digitalWrite(motorPin,LOW);
  delay(3000);
#endif

  delay(2000);

#ifndef GY91
  sleepNow();

  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, true);
#else
  do {
    if(buttonPressed){
      controlVind(false);
      delay(500);
      buttonPressed = false;
      return;
    }

# ifdef INDUCTION
    controlVind(true);
# endif
    
    now = millis();
  }  while(now - start < DELAY);
  start += DELAY;
#endif
}
