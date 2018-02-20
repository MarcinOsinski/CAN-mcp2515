/*
 * spi.c

 *
 *  Created on: 27 paź 2017
 *      Author: rysiek
 */

#include "spi.h"

void SPI_init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);

	// CS as output
	DDR_CS |= (1<<P_CS);
	PORT_CS |= (1<<P_CS);

	/* Enable SPI, Master, set clock rate fck/2 */
	SPCR = (1<<SPE)|(1<<MSTR);
	SPSR = (1<<SPI2X);
}


uint8_t SPI_transmitByte(uint8_t Data)
{
	/* Start transmission */
	SPDR = Data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));

	return SPDR;
}
