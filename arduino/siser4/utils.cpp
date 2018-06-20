#include <Arduino.h>
#include "project.h"

int averageAnalogRead(int pinToRead, uint8_t N){
  unsigned int sum = 0;
  for(uint8_t i = 0 ; i < N ; i++){
    sum += analogRead(pinToRead);
  }
  return sum / N;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
