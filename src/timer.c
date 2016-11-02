/*
 * timer.c
 *
 *  Created on: 2 nov. 2016
 *      Author: Acer
 */


#define T2 0x40090000					//timer2
#define T2IR (*(int *)(T2))				//Interrupt register
#define T2CR (*(int *)(T2 + 0x04))		//control register
#define T2TC (*(int *)(T2 + 0x08))		//Timer Counter register
#define T2PR (*(int *)(T2 + 0x0C))		//Prescaler
#define T2MR0 (*(int *)(T2 + 0x18))		//Match register 0
#define T2MRC (*(int *)(T2 + 0x14))		//match control register
#define ISER0 (*(int *)(0xE000E100))	//Interrupt Set-Enable Register 0
#define PCONP (*(int *)(0x400FC0C4))

#include "images.h"
#include "timer.h"

void timer2Init(){
	//turn on timer 2 (disable default)
	PCONP |= 0x400000;

	//set interrupt settings
	timer2SetPrescaler0(100000);
	timer2SetMatch0(5000, 0x1);
	timer2EnableInterrupt();

	timer2Reset();
}

void timer2ResetInterrupt() {
	//writing high will reset interrupt flag
	T2IR |= 0x01;
}

void timer2Start() {
	T2CR |= 0x01;
}

void timer2Stop() {
	T2CR &= ~0x01;
}

void timer2Reset() {
	T2CR |= 0x02;
	T2CR &= ~0x02;
}

int timer2Value() {
	return T2TC;
}

void timer2SetPrescaler0(int value) {
	T2PR = value;
}

void timer2SetMatch0(int value, char settings) {
	T2MR0 = value;
	T2MRC |= (T2MRC & ~0x07) | (settings & 0x07);
}

void timer2EnableInterrupt(){
	ISER0 |= 0x08;
}

void TIMER2_IRQHandler(){
	timer2ResetInterrupt();

	nextImage();
	timer2Reset();
}
