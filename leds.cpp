#include "leds.h"

const uint8_t PICO_MOSI_MAX7219 = 19;
const uint8_t PICO_CLK_MAX7219 = 18;
const uint8_t PICO_CS_MAX7219 = 13;

LedControl lc=LedControl(PICO_MOSI_MAX7219, PICO_CLK_MAX7219, PICO_CS_MAX7219, 1);

unsigned long delaytime=65;

void leds__wake() {
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void leds__start(){
 
 /*
  lc.setLed(0,0,0,true); // First RGB
  lc.setLed(0,0,3,true); // Second RGB
  lc.setLed(0,1,1,true); // Third RGB
  lc.setLed(0,1,4,true); // Fourth RGB

  // Indicators

  lc.setLed(0,2,0,true); // Right Top LED
  lc.setLed(0,2,5,true); // Left Top LED
*/

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
