/*
 * timeRecorder.c
 *
 *  Created on: 25 okt. 2016
 *      Author: Acer
 */


#define T0 0x40008000				//timer0
#define T0IR (*(int *)(T0))			//Interrupt register
#define T0CR (*(int *)(T0 + 0x04))	//control register
#define T0TC (*(int *)(T0 + 0x08))	//Timer Counter register
#define T0PR (*(int *)(T0 + 0x0C))	//Prescaler
#define T0MR0 (*(int *)(T0 + 0x18))	//Match register 0
#define T0MRC (*(int *)(T0 + 0x14))	//match control register
#define ISER0 (*(int *)(0xE000E100))	//Interrupt Set-Enable Register 0

void timeRecorderInit(int prescaler){
	//set prescaler
	T0PR = prescaler;
}

void timeRecorderStart() {
	T0CR |= 0x01;
}

void timeRecorderStop() {
	T0CR &= ~0x01;
}

void timeRecorderReset(){
	T0CR |= 0x02;
	T0CR &= ~0x02;
}

int timeRecorderValue() {
	return T0TC;
}
