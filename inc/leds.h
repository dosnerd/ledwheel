/*
 * timer0.h
 *
 *  Created on: 6 okt. 2016
 *      Author: Acer
 */

#ifndef LEDS_H_
#define LEDS_H_

void ledsInit(void);
void ledsWrite();
void ledsSetData(unsigned char*, int);
void TIMER0_IRQHandler(void);

#endif /* LEDS_H_ */
