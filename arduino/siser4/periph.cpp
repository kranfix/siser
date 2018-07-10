#include "project.h"

extern DataFrame dt;
FaBo9Axis fabo_9axis;
Adafruit_BMP280 bme;

void setupSensorsAndActuators() {
  // Simple sensors
  pinMode(simplePowerPin, OUTPUT);
  pinMode(complexPowerPin, OUTPUT);
  pinMode(rainPin, INPUT);

#ifdef INDUCTION
  pinMode(pwmIndPin, OUTPUT);
  controlVind(false);
#endif

  pinMode(motorPin, OUTPUT);
}

void readSimpleSensors() {
  DHT dht(DHTPIN, DHTTYPE);
  delay(10);
  dht.begin();

#ifndef DEBUG
  // Rain level meassure
  int rainLevel = averageAnalogRead(rainPin, 8);
  //siser.rain = mapfloat(rainLevel, rain0, rain100, 0.0, 100.0);
  siser.rain = rainLevel;

  int uvLevel = averageAnalogRead(uvPin, 8);
  siser.uv = mapfloat(uvLevel, uv0, uv15, 0.0, 15.0);

  // Lectura del DHT22: Temperatura y Humedad
  siser.dht.t = dht.readTemperature();
  siser.dht.h = dht.readHumidity();

  // Battery level (Volt)
  siser.bat = averageAnalogRead(batPin, 8) * V5 / 1024;
#endif
  dt.addInt("rain", siser.rain);
  //dt.addFloat("uv", siser.uv);
  dt.addInt("uv", 100 * siser.uv);
  dt.Dht(siser.dht.t, siser.dht.h);
  dt.addFloat("bat", siser.bat);
}

float buf[Ncurr];  //  buffer 1
float buf2[Ncurr]; //  buffer 2
CircularBuffer cb(buf, Ncurr);
CircularBuffer cb2(buf2, Ncurr);
void readCurrent() {
  float bias, onlyAC;
  float Ip, Ipa, Ipm;

  unsigned long start, now;

  // Open Loop sensor
  now = micros();
  for (uint8_t i = 0; i < 250; i++) {
    start = now;
    do {
      now = micros();
    } while (now - start < 1000);

    Ip = map(analogRead(olcPin), 0, 480, 0, 1023);
    cb.push(Ip);
    bias = cb.mean();
    onlyAC = Ip - bias;
    cb2.push(onlyAC * onlyAC);
  }
  Ipa = sqrt(cb2.mean());
  Ipm = 0.4501 * Ipa;
  siser.curr.ol = Ipm;

  // Close Loop sensor
  now = micros();
  for (uint16_t i = 0; i < 250; i++) {
    start = now;
    do {
      now = micros();
    } while (now - start < 1000);

    Ip = analogRead(clcPin);
    cb.push(Ip);
    bias = cb.mean();
    onlyAC = Ip - bias;
    cb2.push(onlyAC * onlyAC);
  }
  Ipa = sqrt(cb2.mean());
  Ipm = 0.5775 * Ipa;
  siser.curr.cl = Ipm;
  
  dt.addInt("olc", 100 * siser.curr.ol);
  dt.addInt("clc", 100 * siser.curr.cl);
}

bool readAcc() {
  if (fabo_9axis.begin()) {
    fabo_9axis.readAccelXYZ(&siser.acc.x, &siser.acc.y, &siser.acc.z);
    dt.Acc(siser.acc.x, siser.acc.y, siser.acc.z);
    return true;
  }
  return false;
}

bool readBmp() {
  bool readed = false;
  if (bme.begin(0x76)) {
    volatile float pres = bme.readPressure();
    if (!isnan(pres)) {
      dt.addFloat("pres", pres);
      readed = true;
    }

    volatile float alt = bme.readAltitude();
    if (!isnan(alt)) {
      dt.addFloat("alt", alt);
      readed = true;
    }
  }
  return readed;
}

void controlVind(bool enable) {
  const uint8_t N = 64;
  const float a2v = (R1 + R2) * 5 / (R1 * 1023 * N);
  float e, u, up;
  static float ui = 255;

  uint8_t pwm = 255;
  if (enable) {
    uint16_t analog = 0;
    for (uint8_t i = 0; i < N; i++) {
      analog += analogRead(VindPin);
    }
    float volt = analog * a2v;
    siser.ind.v = volt;

    //Lazo de control
    e = volt - VindRef; // e = y - r
    ui += Ki * e;
    up = Kp * e;
    u = up + ui;
    // Avoiding saturation
    if (u > 254.0) {
      u = 255.0;
    }
    if (u < 1.0) {
      u = 0;
    }
    ui = u - up;
    siser.ind.d = u;
    pwm = siser.ind.d;
  }
  analogWrite(pwmIndPin, pwm);
}
