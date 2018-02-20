/*
 * spi.h
 *
 *  Created on: 27 paź 2017
 *      Author: rysiek
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <util/delay.h>

#define DDR_CS      DDRB
#define PORT_CS     PORTB
#define P_CS        DDB2

#define DDR_SPI		DDRB
#define DD_MOSI		DDB3
#define DD_MISO		DDB4
#define DD_SCK		DDB5

#define DUMMY		0xff

#define CS_LOW		PORT_CS &= ~(1<<P_CS)
#define CS_HIGH		PORT_CS |= (1<<P_CS)

void SPI_init(void);
uint8_t SPI_transmitByte(uint8_t Data);

#endif /* SPI_H_ */
