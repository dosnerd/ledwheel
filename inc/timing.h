/*
 * timing.h
 *
 *  Created on: 25 okt. 2016
 *      Author: Acer
 */

#ifndef TIMING_H_
#define TIMING_H_

void timingInit(int);
void timingResetInterrupt(void);
void timingStart(void);
void timingStop(void);
void timingReset(void);
void timingSetMatch(int);
int timingValue(void);

void TIMER0_IRQHandler(void);
char* propertySelectLine(int*);
char* propertySelectLine2(int*);
unsigned char** propertyLine(unsigned char**);

#endif /* TIMING_H_ */
