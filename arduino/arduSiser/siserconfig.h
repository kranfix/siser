/* Sensors pinout configurations */

// Debug
//#define DEBUG

// Device id:
//    type: byte or uint8_t
//    from 0 to 255
// 0 id is reserved for raspberry
// 7 is reserved for demo in office
// Use from 1 to 6
#define ID 1


// xbeeSerial
#define xbeeSerial Serial1
#define XBEE_INIT {'R','E','Q'}
#define XBEE_INIT_LEN 3

// MQ2 sensor
#define mq2Pin A0

// Rain sensor
#define rainPin A1


// DHT sensor
#define DHTPIN 7
#define DHTTYPE DHT22

// GPS
#define gpsSerial Serial2

// Bluetooth
#define btSerial Serial3

// Lx sensor
#define BH1750_address 0x23
