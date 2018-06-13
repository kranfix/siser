#include <avr/sleep.h>
#include "config.h"

int wakeRtcInterrupt;
int wakeButtonInterrupt;

void wakeUpNow0(){
  
}

void wakeUpNow1(){
  
}

void setupWakeUp(){
  pinMode(wakeRtcPin, INPUT);
  pinMode(wakeButtonPin, INPUT);
  wakeRtcInterrupt = digitalPinToInterrupt(wakeRtcPin);
  wakeButtonInterrupt = digitalPinToInterrupt(wakeButtonPin);
  attachInterrupt(wakeRtcInterrupt, wakeUpNow0, wakeOnRtc);
  attachInterrupt(wakeButtonInterrupt, wakeUpNow1, wakeOnButton);
}

// here we put the arduino to sleep
void sleepNow(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
 
  sleep_enable();       // enables the sleep bit in the mcucr registe
                        // so sleep is possible. just a safety pin

  // use interrupt 0 (pin 2) and run function
  attachInterrupt(wakeRtcInterrupt, wakeUpNow0, wakeOnRtc); // wakeUpNow when pin 2 gets LOW
  attachInterrupt(wakeButtonInterrupt, wakeUpNow1, wakeOnButton); 
                                       
 
  sleep_mode();            // here the device is actually put to sleep!!
                           // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
 
  sleep_disable();         // first thing after waking from sleep:
                           // disable sleep...
  detachInterrupt(wakeRtcInterrupt);     // disables interrupt 0 on pin 2 so the
  detachInterrupt(wakeButtonInterrupt);  // wakeUpNow code will not be executed
                                         // during normal running time.
}

