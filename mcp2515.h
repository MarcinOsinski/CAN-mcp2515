/*
 * mcp2515.h
 *
 *  Created on: 27 paź 2017
 *      Author: rysiek
 */

#ifndef MCP2515_H_
#define MCP2515_H_

#include <avr/io.h>
#include <util/delay.h>

#include "spi.h"


//	SPI COMMANDS
#define RESET		0b11000000
#define READ		0b00000011
#define WRITE		0b00000010
#define READSTATUS	0b10100000
#define RXSTATUS	0b10110000
#define BITMODIFY	0b00000101


//	REGISTER ADDRESSES
#define CNF1		0x2A
#define CNF2		0x29
#define CNF3		0x28
#define CANINTF		0x2C
#define CANINTE		0x2B
#define CANSTAT		0x0E
#define CANCTRL		0x0F
#define RXB1CTRL	0x70
#define RXB1SIDH	0x71
#define RXB1SIDL	0x72
#define RXB1DLC		0x75
#define RXB1D0		0x76
#define RXB1D1		0x77
#define RXB1D2		0x78
#define RXB1D3		0x79
#define RXF2SIDH	0x08
#define RXF2SIDL	0x09
#define RXF3SIDH	0x10
#define RXF3SIDL	0x11
#define RXM1SIDH	0x24
#define RXM1SIDL	0x25

//	BIT DEFINITIONS CNF1
#define SJW1		7
#define SJW0		6
#define BRP5		5
#define BRP4		4
#define BRP3		3
#define BRP2		2
#define BRP1		1
#define BRP0		0

//	BIT DEFINITIONS CNF2
#define BTLMODE		7
#define SAM			6
#define PHSEG12		5
#define PHSEG11		4
#define PHSEG10		3
#define PRSEG2		2
#define PRSEG1		1
#define PRSEG0		0

//	BIT DEFINITIONS CNF3
#define SOF			7
#define WAKFIL		6
#define PHSEG22		2
#define PHSEG21		1
#define PHSEG20		0

//	BIT DEFINITIONS CANINTF
#define MERRF		7
#define WAKIF		6
#define ERRIF		5
#define TX2IF		4
#define TX1IF		3
#define TX0IF		2
#define RX1IF		1
#define RX0IF		0

//	BIT DEFINITIONS CANINTE
#define MERRE		7
#define WAKIE		6
#define ERRIE		5
#define TX2IE		4
#define TX1IE		3
#define TX0IE		2
#define RX1IE		1
#define RX0IE		0

//	BIT DEFINITIONS CANSTAT
#define OPMOD2		7
#define OPMOD1		6
#define OPMOD0		5
#define ICOD2		3
#define ICOD1		2
#define ICOD0		1

//	BIT DEFINITIONS CANCTRL
#define REQOP2		7
#define REQOP1		6
#define REQOP0		5
#define ABAT		4
#define OSM			3
#define CLKEN		2
#define CLKPRE1		1
#define CLKPRE0		0

//	BIT DEFINITIONS RXB1CTRL
#define RXM1		6
#define RXM0		5
#define RXRTR		3
#define FILHIT2		2
#define FILHIT1		1
#define FILHIT0		0

//	BIT DEFINITIONS RXB1SIDH
#define SID10		7
#define SID9		6
#define SID8		5
#define SID7		4
#define SID6		3
#define SID5		2
#define SID4		1
#define SID3		0

//	BIT DEFINITIONS RXB1SIDL
#define SID2		7
#define SID1		6
#define SID0		5
#define SRR			4
#define IDE 		3

//	BIT DEFINITIONS RXB1DLC
#define RTR			6
#define RB1			5
#define RB0			4
#define DLC3		3
#define DLC2		2
#define DLC1		1
#define DLC0		0

//	BIT DEFINITIONS RXB1Dn
#define RBD7		7
#define RBD6		6
#define RBD5		5
#define RBD4		4
#define RBD3		3
#define RBD2		2
#define RBD1		1
#define RBD0		0

//	BIT DEFINITIONS RXF2SIDH
#define SID10		7
#define SID9		6
#define SID8		5
#define SID7		4
#define SID6		3
#define SID5		2
#define SID4		1
#define SID3		0

//	BIT DEFINITIONS RXF2SIDL
#define SID2		7
#define SID1		6
#define SID0		5
#define EXIDE		3

//	BIT DEFINITIONS RXF3SIDH
#define SID10		7
#define SID9		6
#define SID8		5
#define SID7		4
#define SID6		3
#define SID5		2
#define SID4		1
#define SID3		0

//	BIT DEFINITIONS RXF3SIDL
#define SID2		7
#define SID1		6
#define SID0		5
#define EXIDE		3

//	BIT DEFINITIONS RXM1SIDH
#define SID10		7
#define SID9		6
#define SID8		5
#define SID7		4
#define SID6		3
#define SID5		2
#define SID4		1
#define SID3		0

//	BIT DEFINITIONS RXM1SIDL
#define SID2		7
#define SID1		6
#define SID0		5



//	CAN FRAME
struct
{
	uint16_t id;

	struct
	{
		uint8_t rtr : 1;
		uint8_t length : 4;
	} CANheader;

	uint8_t data[8];

} CANframe;



//	MODIFIABLE SPI COMMANDS
void mcp2515_bitModify(uint8_t address, uint8_t mask, uint8_t data);
uint8_t mcp2515_readRxBuf(uint8_t n, uint8_t m);
void mcp2515_loadTxBuf(uint8_t a, uint8_t b, uint8_t c);
void mcp2515_msgReqToSend(uint8_t RTS_TXB2, uint8_t RTS_TXB1, uint8_t RTS_TXB0);



void mcp2515_reset();

void mcp2515_writeRegister(uint8_t address, uint8_t data);
uint8_t mcp2515_readRegister(uint8_t address);


#endif /* MCP2515_H_ */
