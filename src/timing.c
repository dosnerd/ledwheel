/*
 * timing.c
 *
 *  Created on: 25 okt. 2016
 *      Author: Acer
 */

#define T0 0x40004000					//timer1
#define T1IR (*(int *)(T0))				//Interrupt register
#define T1CR (*(int *)(T0 + 0x04))		//control register
#define T1TC (*(int *)(T0 + 0x08))		//Timer Counter register
#define T1PR (*(int *)(T0 + 0x0C))		//Prescaler
#define T1MR0 (*(int *)(T0 + 0x18))		//Match register 0
#define T1MRC (*(int *)(T0 + 0x14))		//match control register
#define ISER0 (*(int *)(0xE000E100))	//Interrupt Set-Enable Register 0

#define IPR0 (*(int *)(0xE000E400))

#include "leds.h"

void timingInit(int prescaler) {
	//set prescaler
	T1PR = prescaler;

	//set interrupt settings (allowed + onreset)
	T1MRC |= (T1MRC & ~0x07) | 0x03;

	//enable interrupt
	ISER0 |= 0x02;

	//set standard value for interrupt
	T1MR0 = 50000;

	//set to a low prior
	IPR0 |= 0xE000;
}

int* propertySelectLine(int * lijn) {
	static int * data;

	//check if used as a setter
	if (lijn != 0) {
		data = lijn;
	}

	return data;
}

int* propertySelectLine2(int * lijn) {
	static int * data;

	//check if used as a setter
	if (lijn != 0) {
		data = lijn;
	}

	return data;
}

unsigned char** propertyLine(unsigned char** dataline) {
	static unsigned char ** data;

	//check if used as a setter
	if (dataline != 0) {
		data = dataline;
	}
	return data;
}

void timingResetInterrupt() {
	//writing high will reset interrupt flag
	T1IR |= 0x01;
}

void timingStart() {
	T1CR |= 0x01;
}

void timingStop() {
	T1CR &= ~0x01;
}

void timingReset() {
	T1CR |= 0x02;
	T1CR &= ~0x02;
}

void timingSetMatch(int value) {
	T1MR0 = value;
}

int timingValue() {
	return T1TC;
}

void TIMER0_IRQHandler() {
	timingResetInterrupt();

	//update (new) line
	unsigned char* dataline = *propertyLine(0);
	ledsSetData(dataline, 288); //(48 * 2) * 3 = 288

	//select next line
	(*propertySelectLine(0))++;
	(*propertySelectLine2(0))++;
}
