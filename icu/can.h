#ifndef CAN_H_
#define CAN_H_

#include <SPI.h>
#include <ACAN2515.h>
#include <Arduino.h>


void can__start();
void can__send_test();
void can__receive();
void can__stop();

#if (POWERTRAIN_TYPE == 'C')
uint16_t can__get_rpm();
uint8_t can__get_gear();
#else //POWERTRAIN_TYPE == 'E'
float can__get_hv();
float can__get_lv();
#endif

#endif /* CAN_H_ */
