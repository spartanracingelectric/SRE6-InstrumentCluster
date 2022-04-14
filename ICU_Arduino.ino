#include "LEDs.h"
#include "CAN.h"

#ifndef ARDUINO_ARCH_RP2040
#error "Select a Raspberry Pi Pico board"
#endif

void setup() {
  CAN_set();
  // Sets up wakeup call for Max7219
  LEDs__wake();
  // Lights all LEDs and then turns off 
  LEDs__start();

}

void loop() {
  // Sends CAN data tests and gets updated on serial
  CAN_update();
}
