/*
 * magnets.c
 *
 *  Created on: 10 okt. 2016
 *      Author: Acer
 */
#define MAGNET0 0x1000
#define MAGNET1 0x40

//48, 53

#define FI20DIR (*(unsigned int *)0x2009C040)		//GPIO direction
#define FIO2SET (*(unsigned int *)0x2009C058)		//GPIO set (can make pin high)
#define FIO2CLR (*(unsigned int *)0x2009C05C)		//GPIO clear (can make pin low)
#define FIO2PIN (*(unsigned int *)0x2009C054) 		//GPIO value (can read and write pin) (write careful! Will effect whole port)#define IO0IntEnR (*(unsigned int *)0x40028090)	//GPIO interrupt set rising edge
#define IO2IntEnF  (*(unsigned int *)0x400280B4)	//GPIO Interrupt Enable Falling edge
#define IO2IntClr (*(unsigned int *)0x400280AC)		//GPIO interrupt clear
#define ISER0  (*(unsigned int *)0xE000E100)		//Interrupt set-enable register

#include "timeRecorder.h"
#include "timing.h"

char side = 0;
int prevVal = 0;

void magnet0Init() {
	//set direction
	FI20DIR &= ~MAGNET0;
	FI20DIR &= ~MAGNET1;
	FI20DIR |= 0x00200000;	//set pin 21 to output

	//interrupt on rising edge
	IO2IntEnF |= MAGNET0;
	IO2IntEnF |= MAGNET1;

	//enable external interrupt 3 (for gpio)
	ISER0 |= 0x200000; //bit 21
}

void EINT3_IRQHandler() {
	//reset interrupt flag
	IO2IntClr |= MAGNET0;
	IO2IntClr |= MAGNET1;

	//get the time that's take the wheel to spin half
	int val = timeRecorderValue();

	//check if other sensor is signaling
	if ((side && (FIO2PIN & MAGNET1)) || (!side && (FIO2PIN & MAGNET0))) {
		side = (FIO2PIN & MAGNET1) == 0;


		if (FIO2PIN & MAGNET1) {
			//add previous time with current
			val += prevVal;

			//save current time
			prevVal = val - prevVal;

			//reset strip 2 (with offset because strip 2 design problems)
			(*propertySelectLine2(0)) = 4;

			//reset record timer
			timeRecorderReset();
		} else {
			//add previous time with current
			val += prevVal;

			//save current time
			prevVal = val - prevVal;

			//reset strip 1
			(*propertySelectLine(0)) = 0;

			//edit timing
			timingStop();
			timingReset();
			timingSetMatch(val / (48 * 2));
			timingStart();

			//reset record timer
			timeRecorderReset();
		}
	}
}
