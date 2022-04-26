#include "leds.h"

MD_MAX72XX *leds;

unsigned long delaytime=65;

void leds__init(MD_MAX72XX *leds_ptr) {
  leds = leds_ptr;
  leds->begin();
}

void leds__wake() {
  
}

void leds__rpm_update(uint16_t rpm) {
  uint8_t leds_to_turn_off;
  uint8_t leds_to_turn_on = 0;
  switch(rpm) {
    case 500 ... 2749:
      leds_to_turn_on = 1;
      break;
    case 2750 ... 4499:
      leds_to_turn_on = 2;
      break;
    case 4500 ... 5999:
      leds_to_turn_on = 3;
      break;
    case 6000 ... 6999:
      leds_to_turn_on = 4;
      break;
    case 7000 ... 7999:
      leds_to_turn_on = 5;
      break;
    case 8000 ... 8999:
      leds_to_turn_on = 6;
      break;
    case 9000 ... 9999:
      leds_to_turn_on = 7;
      break;
    case 10000 ... 10999:
      leds_to_turn_on = 8;
      break;
    case 11000 ... 11999:
      leds_to_turn_on = 9;
      break;
    case 12000 ... 16000:
      leds_to_turn_on = 10;
      break;
    default:
      leds_to_turn_on = 0;
      break;
  }
  //Inverse of # leds ON
  leds_to_turn_off = NUM_LED_SOLID-leds_to_turn_on;
  //Turn on LEDS
  for (uint8_t led_idx = 0; led_idx < leds_to_turn_on; led_idx++) {
    leds->setPoint(PIN_LED_SOLID[led_idx][0],PIN_LED_SOLID[led_idx][1],true);
  }
  //Turn off unused LEDS
  for (uint8_t led_idx = 0; led_idx < leds_to_turn_off; led_idx++) {
    leds->setPoint(PIN_LED_SOLID[NUM_LED_SOLID-led_idx][0],PIN_LED_SOLID[NUM_LED_SOLID-led_idx][1],false);
  }
}

/*
void leds__wake() {
  lc.shutdown(0,false);
  // Set the brightness to a medium values
  lc.setIntensity(0,8);
  // and clear the display
  lc.clearDisplay(0);
}

void leds__start(){
 
 
  lc.setLed(0,0,0,true); // First RGB
  lc.setLed(0,0,3,true); // Second RGB
  lc.setLed(0,1,1,true); // Third RGB
  lc.setLed(0,1,4,true); // Fourth RGB

  // Indicators

  lc.setLed(0,2,0,true); // Right Top LED
  lc.setLed(0,2,5,true); // Left Top LED


  for(int row = 0; row < 5; row++){
      for(int col = 0; col < 10; col++){
            lc.setLed(0, row, col, false);
            delay(delaytime);
            lc.setLed(0, row, col, true); 
      }
  }

   for(int row = 0; row < 5; row++){
      for(int col = 0; col < 10; col++){
            lc.setLed(0, row, col, false);
            delay(delaytime);
      }
  }
  

}
*/