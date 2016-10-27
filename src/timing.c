/*
 * timing.c
 *
 *  Created on: 25 okt. 2016
 *      Author: Acer
 */

#define T0 0x40004000				//timer0
#define T0IR (*(int *)(T0))			//Interrupt register
#define T0CR (*(int *)(T0 + 0x04))	//control register
#define T0TC (*(int *)(T0 + 0x08))	//Timer Counter register
#define T0PR (*(int *)(T0 + 0x0C))	//Prescaler
#define T0MR0 (*(int *)(T0 + 0x18))	//Match register 0
#define T0MRC (*(int *)(T0 + 0x14))	//match control register
#define ISER0 (*(int *)(0xE000E100))	//Interrupt Set-Enable Register 0

#define IPR0 (*(int *)(0xE000E400))

/*
 * NOTE:
 * To use timer 3/4, you need to enable it.
 * This can be done by setting PCTIM2/3 in the PCONP
 */

#include "leds.h"

void timingInit(int prescaler) {
	//set prescaler
	T0PR = prescaler;

	//set interrupt settings (allowed + onreset)
	T0MRC |= (T0MRC & ~0x07) | 0x03;

	//enable interrupt
	ISER0 |= 0x02;

	//set standard value for interrupt
	T0MR0 = 50000;

	//set to a low prior
	IPR0 |= 0xF000;
}

int* propertySelectLine(int * lijn) {
	static int * data;
	if (lijn != 0) {
		data = lijn;
	}

	return data;
}

unsigned char** propertyLine(unsigned char** dataline) {
	static unsigned char ** data;
	if (dataline != 0) {
		data = dataline;
	}
	return data;
}

int timingSetGetAcc(int acc) {
	static int data;
	if (acc != 0) {
		data = acc;
	}

	return data;
}

void timingResetInterrupt() {
	//writing high will reset interrupt flag
	T0IR |= 0x01;
}

void timingStart() {
	T0CR |= 0x01;
}

void timingStop() {
	T0CR &= ~0x01;
}

void timingReset() {
	T0CR |= 0x02;
	T0CR &= ~0x02;
}

void timingSetMatch(int value) {
	T0MR0 = value;
}

void TIMER0_IRQHandler() {
	timingResetInterrupt();

	//update (new) line
	unsigned char* dataline = *propertyLine(0);
	ledsSetData(dataline, 288); //(48 * 2) * 3 = 288

	//select next line
	(*propertySelectLine(0))++;



	//update acceleration
	if (T0MR0 + timingSetGetAcc(0) > 150) {
		T0MR0 += timingSetGetAcc(0);
	}
}
