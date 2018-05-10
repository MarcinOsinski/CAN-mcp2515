#ifndef CAN_H_
#define CAN_H_

#include <avr/io.h>
#include <util/delay.h>

#include "mcp2515.h"

void mcp2515_init();

uint8_t CAN_whichMessage();
void CAN_message1(volatile uint8_t *flagToSet1, volatile uint8_t *flagToSet2);
void CAN_message2(volatile uint8_t *flagToSet);


#endif /* CAN_H_ */


