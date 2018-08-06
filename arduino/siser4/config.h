/* Sensors pinout configurations */

// Debug
//#define DEBUG

// Complex sensors
//#define RTC_dev
//#define GY91
#define CURRENT
#define complexPowerPin 7

// Device id:
//    type: byte or uint8_t
//    from 01 to 99
// id=00 is reserved for raspberry
// Use from 1 to 255
#define ID "05"
#define TYPE "siser4"

/* Communication */
#define commPowerPin 10
#define xbee Serial

/* Simple sensor */
#define simplePowerPin 6

// Rain sensor
#define rainPin A1
#define rain0   1023
#define rain100 200

// UV sensor
#define uvPin A0
#define uv0  200
#define uv15 600

// DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT21

/* Leakage current */
#define olcPin A7
#define clcPin A6
#define Ncurr 48

// Battery Pin
#define batPin A2
#define V5 4.8 // Arduino 5V pin real voltage

/* Induction current */
#define INDUCTION
#define VindPin A3  
#define pwmIndPin 9
#define R1 3.3
#define R2 10.0
#define VindRef 12
//#define Ki 100*0.0001*64
#define Ki 0.64
#define Kp 3

/* Motor de limpieza */
//#define MOTOR
#define motorPin 5
#define motorTime 8000

/* Interrupt pines */
// Attachable Pin: 2 and 3 in Arduino Nano
#define wakeRtcPin 2      // pin used for waking up
#define wakeOnRtc  LOW

#define wakeButtonPin 3   // pin used for waking up
#define wakeOnButton  LOW

/* RTC configutation */
// Frecuencia de wake-up
#define wakeUpFreq 0xC // each hour
//#define wakeUpFreq 0xE // each minute

#define hh1 18
#define mm1 19
#define ss1 00

#define DELAY 3600000 // 3600 s
//#define DELAY 60000 // 100 s

/* EEPROM */
#define RtcSetDir 0
