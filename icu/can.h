#ifndef CAN_H_
#define CAN_H_

#include <SPI.h>
#include <ACAN2515.h>
#include <Arduino.h>


void can__start();
void can__send_test();
void can__receive();
uint16_t can__get_rpm();
uint8_t can__get_gear();
void can__stop();


#endif /* CAN_H_ */
