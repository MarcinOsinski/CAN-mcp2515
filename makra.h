#ifndef MAKRA_H_
#define MAKRA_H_

#define CLEAR(PORT,NUMER)				PORT &= ~(1 << NUMER)
#define SET(PORT,NUMER)					PORT |=  (1 << NUMER)

#define CHECK_1_AT(REGISTER,PIN)		REGISTER & (1 << PIN)
#define CHECK_0_AT(REGISTER,PIN)		!(REGISTER & (1 << PIN))

#define COUNTER0_START	TCCR0|=((1<<CS02)|(1<<CS00))
#define COUNTER1_START	TCCR1B|=((1<<CS02)|(1<<CS00))

#endif /* MAKRA_H_ */
