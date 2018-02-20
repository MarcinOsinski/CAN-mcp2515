/*
 * can.h
 *
 *  Created on: 24 gru 2017
 *      Author: rysiek
 */

#ifndef CAN_H_
#define CAN_H_

#include <avr/io.h>
#include <util/delay.h>

#include "mcp2515.h"

void mcp2515_init();

uint8_t flaga1;
uint8_t flaga2;
uint8_t flaga3;

uint8_t CAN_ktoraWiadomosc();
void CAN_wiadomosc1(uint8_t flagaDoUstawienia1, uint8_t flagaDoUstawienia2);
void CAN_wiadomosc2(uint8_t flagaDoUstawienia);


#endif /* CAN_H_ */
