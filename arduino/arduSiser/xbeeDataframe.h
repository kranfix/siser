#include "siserconfig.h"

byte xbeeInit[3] = XBEE_INIT;
byte xbeeInitLen = XBEE_INIT_LEN;

boolean xbeeLisening() {
  byte counter = 0;
  while(xbeeSerial.available()){
    byte data = xbeeSerial.read();
    if(counter == xbeeInitLen && data == ID){
      return true;
    } else if(data == xbeeInit[counter]) {
      counter++;
    }
  }
  return false;
}
