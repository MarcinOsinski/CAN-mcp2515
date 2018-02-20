/*
 * main.c
 *
 *  Created on: 29 wrz 2017
 *      Author: rysiek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "mcp2515.h"
#include "spi.h"
#include "can.h"
#include "makra.h"

void hello1()
{
	ZERUJ(PORTC,DDC0);
	_delay_ms(500);
	USTAW(PORTC,DDC0);

	ZERUJ(PORTC,DDC1);
	_delay_ms(500);
	USTAW(PORTC,DDC1);

	ZERUJ(PORTC,DDC2);
	_delay_ms(500);
	USTAW(PORTC,DDC2);

	ZERUJ(PORTC,DDC5);
	_delay_ms(500);
	USTAW(PORTC,DDC5);
}

void hello2()
{
	ZERUJ(PORTC,DDC1);
	_delay_ms(500);
	USTAW(PORTC,DDC1);

	ZERUJ(PORTC,DDC0);
	_delay_ms(500);
	USTAW(PORTC,DDC0);

	ZERUJ(PORTC,DDC2);
	_delay_ms(500);
	USTAW(PORTC,DDC2);
}

int main()
{
	// piny 0,1,2,5 w porcie C jako wyjścia
	DDRC |= ((1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC5));
	// aktywne stanem niskim
	PORTC |= ((1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC5));
	// pin 2 portu D (INT0) jako wejście
	DDRD |= (0<<DDD2);
	// pull-up
	PORTD |= (1<<DDD2);

	sei();	// włącz przerwania globalnie

	GICR |= (1 << INT0);	// włącz przerwania INT0 (aktywne stanem niskim)

	hello();

	SPI_init();
	mcp2515_init();


	while(1)
	{
		// sterowanie LED-ami
		if(flaga1)
			ZERUJ(PORTC, DDC0);
		if(!flaga1)
			USTAW(PORTC, DDC0);

		if(flaga2)
			ZERUJ(PORTC, DDC1);
		if(!flaga2)
			USTAW(PORTC, DDC1);

		if(flaga3)
			ZERUJ(PORTC, DDC2);
		if(!flaga3)
			USTAW(PORTC, DDC2);

		if(flaga1 && flaga2 && flaga3)
		{
			// włącz przekaźnik
			ZERUJ(PORTC,DDC5);
		}

		if(!(flaga1 && flaga2 && flaga3))
		{
			// wyłącz przekaźnik
			USTAW(PORTC,DDC5);
		}
	}

}

ISR(INT0_vect)
{
	// bufor pełny - procedura odbierania wiadomości;
	/*if(mcp2515_readRegister(CANINTF) & (1<<MERRF))
		hello2();

	if(mcp2515_readRegister(CANINTF) & (1<<RX1IF))
		hello1();*/

	hello2();

	switch(CAN_ktoraWiadomosc())
	{
		case 0:
		// error
		break;

		case 1:
			CAN_wiadomosc1(flaga1, flaga2);
			break;

		case 2:
			CAN_wiadomosc2(flaga3);
			break;

	}

	// czyszczenie wszystkich flag przerwań - koniec obsługi przerwania
	mcp2515_writeRegister(CANINTF, 0x00);

}

