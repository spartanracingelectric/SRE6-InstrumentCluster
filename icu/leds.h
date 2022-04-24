#include <Arduino.h>
#include <MD_MAX72xx.h>
//#include <LedControl.h>

#ifndef LEDS_H_
#define LEDS_H_

void leds__init(MD_MAX72XX *leds_ptr);
void leds__wake();
void leds__start();

//create LEDs Update function that takes CAN data and changes LEDs


#endif /* LEDS_H_ */
