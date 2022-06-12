#ifndef CAN_H_
#define CAN_H_

#include <SPI.h>
#include <ACAN2515.h>
#include <Arduino.h>


void can__start();
void can__send_test();
void can__receive();

// C car
uint16_t can__get_rpm(const CANMessage & inMessage);
uint8_t can__get_gear(const CANMessage & inMessage);
uint8_t can__get_oiltemp(const CANMessage & inMessage);
uint8_t can__get_engtemp(const CANMessage & inMessage); // C car engine

// E car
uint16_t can__get_hv(const CANMessage & inMessage);
uint8_t can__get_soc(const CANMessage & inMessage);
uint8_t can__get_wattemp(const CANMessage & inMessage);
uint8_t can__get_acctemp(const CANMessage & inMessage); // E car accumulator

// E & C car
uint8_t can__get_lv(const CANMessage & inMessage);
uint8_t can__get_drs(const CANMessage & inMessage);




void can__stop();


#endif /* CAN_H_ */
