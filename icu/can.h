#include <ACAN2515.h>
#include <Arduino.h>

#ifndef CAN_H_
#define CAN_H_


void can__start();
void can__send_test();
void can__receive();
uint16_t can__get_rpm();
void can__stop();


#endif /* CAN_H_ */
