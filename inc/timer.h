/*
 * timer.h
 *
 *  Created on: 2 nov. 2016
 *      Author: Acer
 */

#ifndef TIMER_H_
#define TIMER_H_

void timer2Init(void);
void timer2ResetInterrupt(void);
void timer2Start(void);
void timer2Stop(void);
void timer2Reset(void);
int timer2Value(void);
void timer2SetPrescaler0(int value);
void timer2SetMatch0(int value, char settings);
void timer2EnableInterrupt(void);
void TIMER2_IRQHandler(void);


#endif /* TIMER_H_ */
