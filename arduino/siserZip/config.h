/* Sensors pinout configurations */
#include <Arduino.h>  

// Debug
#define DEBUG

// Device id:
//    type: byte or uint8_t
//    from 0 to 255
// 0 id is reserved for raspberry
// 7 is reserved for demo in office
// Use from 1 to 6
#define ID 7

// xbeeSerial
#define xbeeSerial Serial
#define XBEE_INIT {'R','E','Q'}
#define XBEE_INIT_LEN 3

// MQ2 sensor
#define mq2Pin  A15 // GPIO12, ADC15

// Rain sensor
#define rainPin A13 // GPIO15, ADC13

// DHT sensor
#define DHTPIN 13
#define DHTTYPE DHT22

// GPS
#define gpsSerial Serial2

// Lx sensor
#define BH1750_address 0x23
