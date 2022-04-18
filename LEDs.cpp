#include "LEDs.h"

const uint8_t MAX_PICO_TX = 19;
const uint8_t MAX_PICO_CLK = 18;
const uint8_t MAX_PICO_CS = 13;

LedControl lc=LedControl(MAX_PICO_TX, MAX_PICO_CLK, MAX_PICO_CS, 1);

unsigned long delaytime=65;

void LEDs__wake() {
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void LEDs__start(){
 
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
