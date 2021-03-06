/* Sensors pinout configurations */

// Debug
//#define DEBUG

// Setting EEPROM memory
//#define CLEAREEPROM

// Device id:
//    type: byte or uint8_t
//    from 0 to 255
// 0 id is reserved for raspberry
// Use from 1 to 255
#define ID 1
#define TYPE "siser2"

// Rain sensor
#define rainPin A2


// DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT22

// Battery Pin
#define batPin A3

// Attachable Pin: 2 and 3 in Arduino Nano
#define wakeRtcPin 2     // pin used for waking up
#define wakeOnRtc  LOW

#define wakeButtonPin 3     // pin used for waking up
#define wakeOnButton  LOW

// EEPROM
#define RtcSetDir 0


// Arduino 5V pin real voltage
#define V5 4.6

// Frecuencia de wake-up
#define wakeUpFreq 0xC
