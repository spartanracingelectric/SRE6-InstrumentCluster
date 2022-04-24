#include "leds.h"
#include "can.h"
#include "lcd.h"

#ifndef ARDUINO_ARCH_RP2040
#error "Select a Raspberry Pi Pico board"
#endif

void setup() {
  // Sets up wakeup call for Max7219
  leds__wake();
  // Lights all LEDs and then turns off 
  leds__start();
  can__set();

}

void loop() {
  // Sends CAN data tests and gets updated on serial
  can__update();
}
