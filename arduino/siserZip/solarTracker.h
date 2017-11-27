/*
A solar tracker based on SG90 servo and ESP32
*/

struct solarTacker_servos_t {
  int azimut; // XY plane
  int polar;  // respect Z axis
}

struct solarTacker_ldr_t {
  int lt; // left-top
  int rt; // right-top
  int ld; // left-down
  int rd; // right-down
}

struct solarTacker_t {
  // setting values
  solarTacker_servos_t servoPin;
  solarTacker_ldr_t ldrPin;
  solarTacker_ldr_t ldrChannel;

  // variable to set in loop
  solarTacker_servos_t servoVal;
};

solarTacker_begin(solarTacker_t * st);
solarTacker_loop(solarTacker_t * st);
