/*
 * timeRecorder.c
 *
 *  Created on: 25 okt. 2016
 *      Author: Acer
 */


#define T1 0x40008000					//timer1
#define T1IR (*(int *)(T1))				//Interrupt register
#define T1CR (*(int *)(T1 + 0x04))		//control register
#define T1TC (*(int *)(T1 + 0x08))		//Timer Counter register
#define T1PR (*(int *)(T1 + 0x0C))		//Prescaler
#define T1MR0 (*(int *)(T1 + 0x18))		//Match register 0
#define T1MRC (*(int *)(T1 + 0x14))		//match control register
#define ISER0 (*(int *)(0xE000E100))	//Interrupt Set-Enable Register 0

void timeRecorderInit(int prescaler){
	//set prescaler
	T1PR = prescaler;
}

void timeRecorderStart() {
	T1CR |= 0x01;
}

void timeRecorderStop() {
	T1CR &= ~0x01;
}

void timeRecorderReset(){
	T1CR |= 0x02;
	T1CR &= ~0x02;
}

int timeRecorderValue() {
	return T1TC;
}
