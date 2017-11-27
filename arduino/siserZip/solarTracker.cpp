#include "solarTracker.h"

const int lowerThreshold = 1 * 256 / 20;
const int upperThreshold = 2 * 256 / 20;
const int middle = (lowerThreshold + upperThreshold) / 2;

solarTacker_begin(solarTacker_t * st){
  ledcAttachPin(st->servoPin.azimut, st->servoChannel.azimut);
  ledcAttachPin(st->servoPin.polar,  st->servoChannel.polar);

  ledcSetup(st->servoChannel.azimut, 50, 8); // 50Hz PWM, 8-bit resolution
  ledcSetup(st->servoChannel.polar, 50, 8);  // 50Hz PWM, 8-bit resolution

  st->servoVal.azimut = middle;
  st->servoVal.polar  = middle;

  ledcWrite(st->servoChannel.azimut, st->servoVal.azimut);
  ledcWrite(st->servoChannel.polar,  st->servoVal.polar);
}

solarTacker_loop(solarTacker_t * st) {
  int lt = analogRead(st->ldrPin.lt); // top left
  int rt = analogRead(st->ldrPin.rt); // top right
  int ld = analogRead(st->ldrPin.ld); // down left
  int rd = analogRead(st->ldrPin.rd); // down rigt

  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  if (avl > avr && st->servoVal.azimut > lowerThreshold){
    st->servoVal.azimut--;
  } else if (avl < avr && st->servoVal.azimut < upperThreshold) {
    st->servoVal.azimut++;
  }
  ledcWrite(st->servoChannel.azimut, st->servoVal.azimut);

  if (avt > avd && st->servoVal.polar < upperThreshold){
    st->servoVal.polar++;
  } else if (avt < avd && st->servoVal.polar > lowerThreshold){
    st->servoVal.polar--;
  }
  ledcWrite(st->servoChannel.polar, st->servoVal.polar);
}
