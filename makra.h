/*
 * makra.h
 *
 *  Created on: 30 gru 2017
 *      Author: rysiek
 */

#ifndef MAKRA_H_
#define MAKRA_H_

#define ZERUJ(PORT,NUMER)				PORT &= ~(1 << NUMER)
#define USTAW(PORT,NUMER)				PORT |=  (1 << NUMER)

#define SPRAWDZ_1_NA(PIN,NUMER)			PIN & (1 << NUMER)
#define SPRAWDZ_0_NA(PIN,NUMER)			!(PIN & (1 << NUMER))

#endif /* MAKRA_H_ */
