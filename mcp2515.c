/*
 * mcp2515.c
 *
 *  Created on: 27 paź 2017
 *      Author: rysiek
 */

#include "mcp2515.h"


void mcp2515_reset()
{
	CS_LOW;

	SPI_transmitByte(RESET);

	CS_HIGH;
}

void mcp2515_writeRegister(uint8_t address, uint8_t data)
{
	CS_LOW;

	SPI_transmitByte(WRITE);
	SPI_transmitByte(address);
	SPI_transmitByte(data);

	CS_HIGH;
}

uint8_t mcp2515_readRegister(uint8_t address)
{
	uint8_t data;

	CS_LOW;

	SPI_transmitByte(READ);
	SPI_transmitByte(address);

	data = SPI_transmitByte(DUMMY);

	CS_HIGH;

	return data;
}

void mcp2515_bitModify(uint8_t address, uint8_t mask, uint8_t data)
{
	CS_LOW;

	SPI_transmitByte(BITMODIFY);
	SPI_transmitByte(address);
	SPI_transmitByte(mask);
	SPI_transmitByte(data);

	CS_HIGH;
}

uint8_t mcp2515_readRxBuf(uint8_t n, uint8_t m)
{
	uint8_t command = 0b10010000;
	command |= (n << 2);
	command |= (m << 1);

	uint8_t data;

	CS_LOW;
		SPI_transmitByte(command);
		data = SPI_transmitByte(DUMMY);
	CS_HIGH;

	return data;
}

void mcp2515_loadTxBuf(uint8_t a, uint8_t b, uint8_t c)
{
	CS_LOW;

	CS_HIGH;
}

void mcp2515_msgReqToSend(uint8_t RTS_TXB2, uint8_t RTS_TXB1, uint8_t RTS_TXB0)
{
	CS_LOW;

	CS_HIGH;
}
