#ifndef CAN_H_
#define CAN_H_

#include <SPI.h>
#include <ACAN2515.h>
#include <Arduino.h>


void can__start();
void can__send_test();
void can__receive();

// C car
uint16_t can__get_rpm();
uint8_t can__get_gear();
uint8_t can__get_oiltemp();
uint8_t can__get_engtemp(); // C car engine

// E car
uint16_t can__get_hv();
uint8_t can__get_soc();
uint8_t can__get_wattemp();
uint8_t can__get_acctemp(); // E car accumulator

// E & C car
uint8_t can__get_lv();
uint8_t can__get_drs();




void can__stop();


#endif /* CAN_H_ */
