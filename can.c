#include "can.h"
#include "makra.h"

void mcp2515_init()
{
	CS_LOW;

	mcp2515_reset();

	_delay_ms(60000);

	mcp2515_writeRegister(CNF1, 0x01);
	mcp2515_writeRegister(CNF2, 0x9a);
	mcp2515_writeRegister(CNF3, 0x07);


	mcp2515_writeRegister(CANINTE, (1<<RX0IE));

	mcp2515_writeRegister(RXF0SIDH, ((1<<SID7)|(1<<SID8)));
	mcp2515_writeRegister(RXF0SIDL, (1<<SID1));

	mcp2515_writeRegister(RXF1SIDH, ((1<<SID5)|(1<<SID6)|(1<<SID7)|(1<<SID8)));
	mcp2515_writeRegister(RXF1SIDL, (1<<SID2));

	mcp2515_writeRegister(RXM0SIDH, 0xff);
	mcp2515_writeRegister(RXM0SIDL, 0xe0);

	mcp2515_writeRegister(CANCTRL, 0);

	CS_HIGH;
}

uint8_t CAN_whichMessage()
{
	uint8_t rxb0ctrl;
	uint8_t filhit;

	rxb0ctrl = mcp2515_readRegister(RXB0CTRL);

	if(CHECK_1_AT(rxb0ctrl,FILHIT0))
		filhit = 2;
	else
		filhit = 1;

	return filhit;
}

void CAN_message1(volatile uint8_t *flagToSet1, volatile uint8_t *flagToSet2)
{
	uint8_t dataByte;

	dataByte = mcp2515_readRegister(RXB0D0);

	if(CHECK_1_AT(dataByte,5))
		*flagToSet1 = 1;

	else
		*flagToSet1 = 0;

	dataByte = mcp2515_readRegister(RXB0D3);

	if(CHECK_1_AT(dataByte,0))
		*flagToSet2 = 1;

	else
		*flagToSet2 = 0;

}

void CAN_message2(volatile uint8_t *flagToSet3)
{
	uint32_t number;

	uint8_t byte0;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;


	byte0 = mcp2515_readRegister(RXB0D0);
	byte1 = mcp2515_readRegister(RXB0D1);
	byte2 = mcp2515_readRegister(RXB0D2);
	byte3 = mcp2515_readRegister(RXB0D3);


	number = ((uint32_t)byte3 << 24) | ((uint32_t)byte2 << 16) |
				((uint32_t)byte1 << 8) | ((uint32_t)byte0);

	if((number > 1000) && (number < 100000))
		*flagToSet3 = 1;

	else
		*flagToSet3 = 0;
}
