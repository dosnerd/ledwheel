/*
 * timer1.c
 *
 *  Created on: 6 okt. 2016
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

/*
 * NOTE:
 * To use timer 3/4, you need to enable it.
 * This can be done by setting PCTIM2/3 in the PCONP
 */

void timer0ResetInterrupt() {
	//writing high will reset interrupt flag
	T0IR |= 0x01;
}

void timer0Start() {
	T0CR |= 0x01;
}

void timer0Stop() {
	T0CR &= ~0x01;
}

void timer0Reset() {
	T0CR |= 0x02;
	T0CR &= ~0x02;
}

int timer0Value() {
	return T0TC;
}

void timer0SetPrescaler0(int value) {
	T0PR = value;
}

void timer0SetMatch0(int value, char settings) {
	T0MR0 = value;
	T0MRC |= (T0MRC & ~0x07) | (settings & 0x07);
}

void timer0EnableInterrupt(){
	ISER0 |= 0x02;
}
