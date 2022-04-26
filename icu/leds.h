#include <Arduino.h>
#include <MD_MAX72xx.h>
//#include <LedControl.h>

#ifndef LEDS_H_
#define LEDS_H_

/*---------------------------------------------------------------------------/
/ LED MAP TO MAX7219 ROW/COLUMN
/---------------------------------------------------------------------------*/
// Solid state LED map
// 10 array rows per Solid State LED, 2 array columns for MAX7219 row & column # respectively
const uint8_t NUM_LED_SOLID = 10;
const uint8_t NUM_LED_RGB = 6;
const uint8_t PIN_LED_SOLID[NUM_LED_SOLID][2] = {{0,0}, {0,1}, {0,2}, {0,3}, {0,4},
                                                {0,5}, {1,1}, {1,2}, {1,3}, {1,4}};

// RGB LED map (Todo)
// 6 array rows per RGB LED number (red only), 2 array columns per MAX7219 {row, column}
//const uint8_t PIN_LED_RGB_R[NUM_LED_RGB][2];
// 6 array rows per RGB LED number (green only), 2 array columns per MAX7219 {row, column}
//const uint8_t PIN_LED_RGB_G[NUM_LED_RGB][2];
// 6 array rows per RGB LED number (blue only), 2 array columns per MAX7219 {row, column}
//const uint8_t PIN_LED_RGB_B[NUM_LED_RGB][2];

void leds__init(MD_MAX72XX *leds_ptr);
void leds__wake();
void leds__start();
void leds__rpm_update(uint16_t rpm);

//create LEDs Update function that takes CAN data and changes LEDs


#endif /* LEDS_H_ */
