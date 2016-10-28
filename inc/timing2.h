/*
 * timing.h
 *
 *  Created on: 25 okt. 2016
 *      Author: Acer
 */

#ifndef TIMING2_H_
#define TIMING2_H_

void timing2Init(int);
void timing2ResetInterrupt();
void timing2Start();
void timing2Stop();
void timing2Reset();
void timing2SetMatch(int);
int timing2SetGetAcc(int);

void TIMER2_IRQHandler(void);
char* propertySelectLine2(int*);

#endif /* TIMING_H_ */
