/* Sensors pinout configurations */

// Debug
//#define DEBUG

// Setting EEPROM memory
//#define CLEAREEPROM

// Device id:
//    type: byte or uint8_t
//    from 01 to 99
// id=00 is reserved for raspberry
// Use from 1 to 255
#define ID "06"
#define TYPE "siser3"

// Sensors power control
#define sensorPowerPin 5

// Xbee power control
#define xbeePowerPin 5

// Rain sensor
#define rainPin A0
#define rain0   0
#define rain100 1023

// UV sensor
#define uvPin A2
#define uvMin 200
#define uvMax 593

// DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT21

// Battery Pin
#define batPin A6

// Attachable Pin: 2 and 3 in Arduino Nano
#define wakeRtcPin 2     // pin used for waking up
#define wakeOnRtc  LOW
  
#define wakeButtonPin 3     // pin used for waking up
#define wakeOnButton  LOW

// EEPROM
#define RtcSetDir 0

// Arduino 5V pin real voltage
#define V5 5.0

// Frecuencia de wake-up
#define wakeUpFreq 0xC // each hour
//#define wakeUpFreq 0xE // each minute

#define hh1 18
#define mm1 55
#define ss1 00

