/*
A solar tracker based on SG90 servo and ESP32
*/

struct solarTracker_servos_t {
  int azimut; // XY plane
  int polar;  // respect Z axis
};

struct solarTracker_ldr_t {
  int lt; // left-top
  int rt; // right-top
  int ld; // left-down
  int rd; // right-down
};

struct solarTracker_t {
  // setting values
  solarTracker_servos_t servoPin;
  solarTracker_servos_t servoChannel;
  solarTracker_ldr_t ldrPin;

  // variable to set in loop
  solarTracker_servos_t servoVal;
};

void solarTracker_begin(solarTracker_t * st);
void solarTracker_loop(solarTracker_t * st);
