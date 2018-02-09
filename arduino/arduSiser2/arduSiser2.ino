#include "config.h"
#include <DHT.h>
#include "siser.h"
#include "sleep.h"
#include <RTClibExtended.h>
#include <EEPROM.h>

RTC_DS3231 RTC;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

#ifdef CLEAREEPROM
  Serial.println("Iniciando borrado de ");
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  delay(100);
  Serial.println("Limpiado de EEPROM terminado.");
  Serial.println("Reprogramar sin la constante CLEAREEPROM");
  for(;;);
#else
  Serial.println("Iniciando lectura de EEPROM");
  if(EEPROM.read(RtcSetDir) == 0){
    // Here goes code for setting RTC
    // date and time in compilation time
    
    Serial.println("Ingresé a configurar RTC");
    EEPROM.write(RtcSetDir, 1);
  } else {
    Serial.println("No ingresé a configurar RTC");
  }
  Serial.println("Etapa de configuracion de RTC terminada");
  delay(100);
#endif
  
  pinMode(rainPin, INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  dht.begin();

  //Wire.begin();
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

  //Set alarm1 every day at 18:33
  RTC.setAlarm(0xC, 30, 20, 18, 0);   //set your wake-up time here
  RTC.alarmInterrupt(1, true);
  
  setupWakeUp();
}

void loop() {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000); // delay for restablish the meassures
#ifndef DEBUG
  readSensors();
#endif

  char buf[128];
  int n = dataframeToString(&siser,buf);
  Serial.write(buf,n);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  sleepNow();

  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, true);
}

#ifndef DEBUG
void readSensors() {
  // Rain level meassure
  int rainLevel = analogRead(rainPin);
  siser.rain = map(rainLevel, 460, 1023, 0, 100);

  // Lectura del DHT22: Temperatura y Humedad
  siser.dht.t = dht.readTemperature();
  siser.dht.h = dht.readHumidity();

  // Battery level (Volt)
  siser.bat = analogRead(batPin) * 5.0 / 1024;
}
#endif
