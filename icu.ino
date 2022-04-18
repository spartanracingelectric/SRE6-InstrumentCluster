#include "leds.h"
#include "can.h"
#include <ACAN2515.h>

#ifndef ARDUINO_ARCH_RP2040
#error "Select a Raspberry Pi Pico board"
#endif


// Using SPI
static const byte PICO_SCK_MCP2515  = 18; // SCK input of MCP2515
static const byte PICO_MOSI_MCP2515 = 19; // SDI input of MCP2515
static const byte PICO_MISO_MCP2515 = 16; // SDO output of MCP2517

static const byte PICO_CS_MCP2515  = 17;  // CS input of MCP2515 (adapt to your design)
static const byte PICO_INT_MCP2515 = 15;  // INT output of MCP2515 (adapt to your design)

void setup() {
  //--- Start serial
  Serial.begin (115200);
  
  //--- Wait for serial (blink led at 10 Hz during waiting)
  /*
  while (!Serial) {
    delay (50);
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  */
  
  //--- There are no default SPI pins so they must be explicitly assigned
  SPI.setSCK(PICO_SCK_MCP2515);
  SPI.setTX(PICO_MOSI_MCP2515);
  SPI.setRX(PICO_MISO_MCP2515);
  SPI.setCS(PICO_CS_MCP2515);
  
  can__set();
  // Sets up wakeup call for Max7219
  leds__wake();
  // Lights all LEDs and then turns off 
  leds__start();

}

void loop() {
  // Sends CAN data tests and gets updated on serial
  can__update();
}
