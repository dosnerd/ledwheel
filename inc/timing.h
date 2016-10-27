/*
 * timing.h
 *
 *  Created on: 25 okt. 2016
 *      Author: Acer
 */

#ifndef TIMING_H_
#define TIMING_H_

void timingInit(int);
void timingResetInterrupt();
void timingStart();
void timingStop();
void timingReset();
void timingSetMatch(int);
int timingSetGetAcc(int);

void TIMER0_IRQHandler(void);
char* propertySelectLine(int*);
unsigned char** propertyLine(unsigned char**);

#endif /* TIMING_H_ */
