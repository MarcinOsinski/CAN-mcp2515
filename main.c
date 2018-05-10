/*
 * main.c
 *
 *  Created on: 29 wrz 2017
 *      Author: rysiek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdlib.h>
#include <stdio.h>

#include "mcp2515.h"
#include "spi.h"
#include "can.h"
#include "makra.h"


volatile uint8_t flag1 = 0;
volatile uint8_t flag2 = 0;
volatile uint8_t flag3 = 0;

volatile uint8_t timer0;


void hello();
void resetCounter1();


int main()
{
	DDRC |= ((1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC5));
	PORTC |= ((1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC5));
	DDRD |= (0<<DDD2);
	PORTD |= (1<<DDD2);

	OCR1A = 0xffff;
	TCCR1B |= (1<<WGM12);
	TIMSK |= ((1<<OCIE1A)|(1<<TOIE0));

	SPI_init();
	mcp2515_init();

	hello();

	sei();
	GICR |= (1 << INT0);

	COUNTER0_START;
	COUNTER1_START;

	while(1)
	{
		if(flag1 == 1)
			CLEAR(PORTC,DDC0);
		else
			SET(PORTC,DDC0);

		if(flag2 == 1)
			CLEAR(PORTC,DDC1);
		else
			SET(PORTC,DDC1);

		if(flag3 == 1)
			CLEAR(PORTC,DDC2);
		else
			SET(PORTC,DDC2);


		if(flag1 && flag2 && flag3)
			CLEAR(PORTC,DDC5);
		else
			SET(PORTC,DDC5);

		if(timer0 > 250)
		{
			timer0 = 0;

			flag1 = 0;
			flag2 = 0;
		}
	}

}


ISR(INT0_vect)
{
	switch(CAN_whichMessage())
	{
		case 1:
			CAN_message1(&flag1, &flag2);
			timer0 = 0;
			break;

		case 2:
			CAN_message2(&flag3);
			resetCounter1();
			break;
	}

	mcp2515_writeRegister(CANINTF, 0x00);
}

ISR(TIMER0_OVF_vect)
{
	timer0++;
}

ISR(TIMER1_COMPA_vect)
{
	flag3 = 0;
}

void hello()
{
	CLEAR(PORTC, DDC0);
	CLEAR(PORTC, DDC1);
	CLEAR(PORTC, DDC2);
	_delay_ms(1000);
	SET(PORTC, DDC0);
	SET(PORTC, DDC1);
	SET(PORTC, DDC2);
	_delay_ms(500);
	CLEAR(PORTC, DDC0);
	CLEAR(PORTC, DDC1);
	CLEAR(PORTC, DDC2);
	_delay_ms(1000);
	SET(PORTC, DDC0);
	SET(PORTC, DDC1);
	SET(PORTC, DDC2);
	_delay_ms(1000);
}

void resetCounter1()
{
	 unsigned char sreg;
	 /* Save Global Interrupt Flag */
	 sreg = SREG;
	 /* Disable interrupts */
	 cli();
	 TCNT1  = 0;
	 /* Restore Global Interrupt Flag */
	 SREG = sreg;
}

