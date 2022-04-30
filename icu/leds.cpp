#include "leds.h"

MD_MAX72XX *leds;

//unsigned long delaytime=65;

// Keep state of leds to easily toggle later
// Default off
uint8_t pin_led_solid_state[NUM_LED_SOLID] = {0};

//Internal variables
uint32_t prev_millis_overrev = 0;
uint32_t prev_millis_revlim = 0;


void leds__init(MD_MAX72XX *leds_ptr) {
  leds = leds_ptr;
  leds->begin();
}

void leds__wake() {
  for (int led_idx = 0; led_idx < NUM_LED_RGB; led_idx++) {
    leds->setPoint(PIN_LED_RGB_R[led_idx][0],PIN_LED_RGB_R[led_idx][1],true);
    delay(30);
    leds->setPoint(PIN_LED_RGB_G[led_idx][0],PIN_LED_RGB_G[led_idx][1],true);
    delay(30);
    leds->setPoint(PIN_LED_RGB_B[led_idx][0],PIN_LED_RGB_B[led_idx][1],true);
    delay(30);
  }
  for (int led_idx = 0; led_idx < NUM_LED_RGB; led_idx++) {
    leds->setPoint(PIN_LED_RGB_R[led_idx][0],PIN_LED_RGB_R[led_idx][1],false);
    delay(30);
    leds->setPoint(PIN_LED_RGB_G[led_idx][0],PIN_LED_RGB_G[led_idx][1],false);
    delay(30);
    leds->setPoint(PIN_LED_RGB_B[led_idx][0],PIN_LED_RGB_B[led_idx][1],false);
    delay(30);
  }
  //Turn on ALL LEDS
  for (uint8_t led_idx = 0; led_idx < NUM_LED_SOLID; led_idx++) {
    leds->setPoint(PIN_LED_SOLID[led_idx][0],PIN_LED_SOLID[led_idx][1],true);
  }
  delay(75);
  //Turn off ALL LEDS
  for (uint8_t led_idx = 0; led_idx < NUM_LED_SOLID; led_idx++) {
    leds->setPoint(PIN_LED_SOLID[led_idx][0],PIN_LED_SOLID[led_idx][1],false);
  }
  delay(75);
  //Turn on ALL LEDS
  for (uint8_t led_idx = 0; led_idx < NUM_LED_SOLID; led_idx++) {
    leds->setPoint(PIN_LED_SOLID[led_idx][0],PIN_LED_SOLID[led_idx][1],true);
  }
  delay(75);
  //Turn off ALL LEDS
  for (uint8_t led_idx = 0; led_idx < NUM_LED_SOLID; led_idx++) {
    leds->setPoint(PIN_LED_SOLID[led_idx][0],PIN_LED_SOLID[led_idx][1],false);
  }
}

void leds__enable_shift() {
  //Change internal state of all shift leds to HIGH (exclude LED1 and LED10)
  for (uint8_t led_idx = 0; led_idx < NUM_LED_SOLID-2; led_idx++) {
    pin_led_solid_state[led_idx+1] = 1;
    leds->setPoint(PIN_LED_SOLID[led_idx+1][0], PIN_LED_SOLID[led_idx+1][1], true);
  }
  //If edge LEDs turned on, turn off
  if (pin_led_solid_state[1]) {
    pin_led_solid_state[0] = 0;
    pin_led_solid_state[NUM_LED_SOLID-1] = 0;
    leds->setPoint(PIN_LED_SOLID[0][0], PIN_LED_SOLID[0][1], false);
    leds->setPoint(PIN_LED_SOLID[NUM_LED_SOLID-1][0], PIN_LED_SOLID[NUM_LED_SOLID-1][1], false);
  }
}

void leds__disable_shift() {
  //Change internal state of all shift leds to LOW (exclude LED1 and LED10)
  for (uint8_t led_idx = 0; led_idx < NUM_LED_SOLID-2; led_idx++) {
    pin_led_solid_state[led_idx+1] = 0;
    leds->setPoint(PIN_LED_SOLID[led_idx+1][0], PIN_LED_SOLID[led_idx+1][1], false);
  }
}

void leds__disable_all_solid() {
  //Change internal state of all leds to LOW
  for (uint8_t led_idx = 0; led_idx < NUM_LED_SOLID; led_idx++) {
    pin_led_solid_state[led_idx] = 0;
    leds->setPoint(PIN_LED_SOLID[led_idx][0], PIN_LED_SOLID[led_idx][1], false);
  }
}

void leds__toggle_overrev() {
  for (uint8_t led_idx = 1; led_idx < NUM_LED_SOLID-1; led_idx++) {
    // If led on
    if (pin_led_solid_state[led_idx]) {
      // Then turn off
      pin_led_solid_state[led_idx] = 0;
      leds->setPoint(PIN_LED_SOLID[led_idx][0], PIN_LED_SOLID[led_idx][1], false);
    }
    //If led off
    else {
      // Then turn off
      pin_led_solid_state[led_idx] = 1;
      leds->setPoint(PIN_LED_SOLID[led_idx][0], PIN_LED_SOLID[led_idx][1], true);
    }
  }
  //If edge LEDs turned on, turn off
  if (pin_led_solid_state[1]) {
    pin_led_solid_state[0] = 0;
    pin_led_solid_state[NUM_LED_SOLID-1] = 0;
    leds->setPoint(PIN_LED_SOLID[0][0], PIN_LED_SOLID[0][1], false);
    leds->setPoint(PIN_LED_SOLID[NUM_LED_SOLID-1][0], PIN_LED_SOLID[NUM_LED_SOLID-1][1], false);
  }
}

void leds__toggle_revlim() {
  for (uint8_t led_idx = 1; led_idx < NUM_LED_SOLID-1; led_idx++) {
    // If led on
    if (pin_led_solid_state[led_idx]) {
      // Then turn off
      pin_led_solid_state[led_idx] = 0;
      leds->setPoint(PIN_LED_SOLID[led_idx][0], PIN_LED_SOLID[led_idx][1], false);
    }
    //If led off
    else {
      // Then turn off
      pin_led_solid_state[led_idx] = 1;
      leds->setPoint(PIN_LED_SOLID[led_idx][0], PIN_LED_SOLID[led_idx][1], true);
    }
  }
  // Only check first led state, assume rest are same state
  // Rewrite so we don't assume
  // If shift leds already on, turn off edge effect LEDs (mutually exclusive)
  if (pin_led_solid_state[1]) {
    pin_led_solid_state[0] = 0;
    pin_led_solid_state[NUM_LED_SOLID-1] = 0;
    leds->setPoint(PIN_LED_SOLID[0][0], PIN_LED_SOLID[0][1], false);
    leds->setPoint(PIN_LED_SOLID[NUM_LED_SOLID-1][0], PIN_LED_SOLID[NUM_LED_SOLID-1][1], false);
  }
  // Else if shift leds off, turn on edge effect LEDs (mutually exclusive)
  else {
    pin_led_solid_state[0] = 1;
    pin_led_solid_state[NUM_LED_SOLID-1] = 1;
    leds->setPoint(PIN_LED_SOLID[0][0], PIN_LED_SOLID[0][1], true);
    leds->setPoint(PIN_LED_SOLID[NUM_LED_SOLID-1][0], PIN_LED_SOLID[NUM_LED_SOLID-1][1], true);
  }
}
/*
void leds__rpm_update_tach(uint16_t rpm) {
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
*/

void leds__rpm_update_flash(uint16_t rpm, uint32_t curr_millis_flash)
{

  // If between min. shift threshold and overrev threshold, solid shift LED bar
  if (rpm > SHIFT_THRESHOLD_RPM && rpm <= OVERREV_THRESHOLD_RPM) {
    leds__enable_shift();
  }
  
  // Else if between min. overrev threshold and rev limit threshold, toggle LED bar at OVERREV_THRESHOLD_FLASH_MS Hz
  else if (rpm > OVERREV_THRESHOLD_RPM && rpm <= REVLIM_THRESHOLD_RPM) {
    // Time difference between last known toggle (prev_millis_overrev)
    // and current time (curr_millis_flash)
    if (curr_millis_flash-prev_millis_overrev >= OVERREV_THRESHOLD_FLASH_MS) {
      prev_millis_overrev = curr_millis_flash;
      leds__toggle_overrev();
    }
  }
  // Else if between min. overrev threshold and rev limit threshold, toggle LED bar at REVLIM_THRESHOLD_FLASH_MS Hz
  else if (rpm > REVLIM_THRESHOLD_RPM) {
    // Time difference between last known toggle (prev_millis_revlim)
    // and current time (curr_millis_flash)
    if (curr_millis_flash-prev_millis_revlim >= REVLIM_THRESHOLD_FLASH_MS) {
      prev_millis_revlim = curr_millis_flash;
      leds__toggle_revlim();
    }
  }
  //Turn off all LEDs, nothing to show
  else {
    leds__disable_all_solid();
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