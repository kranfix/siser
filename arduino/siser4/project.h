#ifndef PROJECT_H
#define PROJECT_H

#include <Arduino.h>
#include <DHT.h>

#include <didiusJsonIdl.h>

#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <maf.h>

#include "siser.h"
#include "config.h"

void setupSensorsAndActuators();

// Simple sensors
void readSimpleSensors();

// current.cpp
void readCurrent();

// gy91.cpp
bool readAcc();
bool readBmp();

// Induction voltage control
void controlVind(bool enable);

// utils.cpp
int averageAnalogRead(int pinToRead, uint8_t N);
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);

static bool buttonPressed = false;

#endif // PROJECT_H
