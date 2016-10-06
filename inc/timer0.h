/*
 * timer0.h
 *
 *  Created on: 6 okt. 2016
 *      Author: Acer
 */

#ifndef TIMER0_H_
#define TIMER0_H_

void timer0ResetInterrupt(void);
void timer0Start(void);
void timer0Stop(void);
void timer0Reset(void);
int timer0Value(void);
void timer0SetPrescaler0(int);
void timer0SetMatch0(int, char);
void timer0EnableInterrupt();

#endif /* TIMER0_H_ */
