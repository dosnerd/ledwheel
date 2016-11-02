/*
 * timer.h
 *
 *  Created on: 2 nov. 2016
 *      Author: Acer
 */

#ifndef TIMER_H_
#define TIMER_H_

void timer2Init();

void timer2ResetInterrupt();

void timer2Start();

void timer2Stop();

void timer2Reset();

int timer2Value();

void timer2SetPrescaler0(int value);

void timer2SetMatch0(int value, char settings);

void timer2EnableInterrupt();

#endif /* TIMER_H_ */
