/*
 * can.c
 *
 *  Created on: 24 gru 2017
 *      Author: rysiek
 */

#include "can.h"

void mcp2515_init()
{
	CS_LOW;

	mcp2515_reset();

	// REJESTRY BIT TIMING CNF0...1
	mcp2515_writeRegister(CNF1, 0x00);
	mcp2515_writeRegister(CNF2, 0xac);
	mcp2515_writeRegister(CNF3, 0x03);

	// PRZERWANIA
	mcp2515_writeRegister(CANINTE, (1<<RX1IE)|(1<<RX0IE)|(1<<MERRE)); //pin INT aktywny gdy bufor RX1 pełny

	if(mcp2515_readRegister(CANINTE) & (1<<RX1IE));
		hello1();

	// FILTRY I MASKI ODBIORU
	mcp2515_writeRegister(RXB1CTRL, (1<<RXM0)); //akceptacja wiadomości ze standardowym id
	//filtr 2 akceptuje ramki o adresie 182h
	mcp2515_writeRegister(RXF2SIDH, ((1<<SID7)|(1<<SID8)));
	mcp2515_writeRegister(RXF2SIDL, (1<<SID1));
	//filtr 3 akceptuje ramki o adresie 183h
	mcp2515_writeRegister(RXF3SIDH, ((1<<SID7)|(1<<SID8)));
	mcp2515_writeRegister(RXF3SIDL, ((1<<SID1)|(1<<SID0)));
	//maska -> same '1'
	mcp2515_writeRegister(RXM1SIDH, 0xff);
	mcp2515_writeRegister(RXM1SIDL, 0xe0);

	// PRZEJSCIE W TRYB PRACY - KONIEC KONFIGURACJI
	mcp2515_writeRegister(CANCTRL, 0);

	CS_HIGH;
}

uint8_t CAN_ktoraWiadomosc()
{
	// 1. RXB1CTRL - bity FILHIT - informacja ktory filtr
	// 2. RXB1SIDH i RXB1SIDL - ID odebranych ramek
	// 3. RXB1DM - rejestry z danymi (M-nr bajtu)

	// sprawdzenie wg ktorego filtru przyjeto ramke
	uint8_t rxb1ctrl;
	uint8_t filhit;

	CS_LOW;

	rxb1ctrl = mcp2515_readRegister(RXB1CTRL);

	CS_HIGH;

	if(rxb1ctrl & (1<<FILHIT1))
		filhit = 1;
	if(rxb1ctrl & ((1<<FILHIT1)|(1<<FILHIT0)))
		filhit = 2;

	return filhit;
}

void CAN_wiadomosc1(uint8_t flagaDoUstawienia1, uint8_t flagaDoUstawienia2)
{
	uint8_t dataByte;

	CS_LOW;

	dataByte = mcp2515_readRegister(RXB1D0);

	CS_HIGH;

	if(dataByte&(1<<5))
		flagaDoUstawienia1 = 1;

	if(!(dataByte&(1<<5)))
			flagaDoUstawienia1 = 0;

	CS_LOW;

	dataByte = mcp2515_readRegister(RXB1D3);

	CS_HIGH;

	if(dataByte&(1<<0))
		flagaDoUstawienia2 = 1;

	if(!(dataByte&(1<<0)))
		flagaDoUstawienia2 = 0;

}

void CAN_wiadomosc2(uint8_t flagaDoUstawienia)
{
	// 1000 - 1000000 bajty 3 2 1 0
	// 1000    = 00 00 03 E8
	// 1000000 = 00 01 86 A0

	uint32_t liczba;

	uint8_t bajt0;
	uint8_t bajt1;
	uint8_t bajt2;
	uint8_t bajt3;

	CS_LOW;

	bajt0 = mcp2515_readRegister(RXB1D0);
	bajt1 = mcp2515_readRegister(RXB1D1);
	bajt2 = mcp2515_readRegister(RXB1D2);
	bajt3 = mcp2515_readRegister(RXB1D3);

	CS_HIGH;

	liczba = ((uint32_t)bajt3 << 24) | ((uint32_t)bajt2 << 16) |
				((uint32_t)bajt1 << 8) | ((uint32_t)bajt0);

	if((liczba > 1000) && (liczba < 100000))
		flagaDoUstawienia = 1;

	else
		flagaDoUstawienia = 0;
}
