/*
 * timer1.c
 *
 *  Created on: 6 okt. 2016
 *      Author: Acer
 */
#define OUTPUTPIN 0x00200000
#define NOTOUTPUTPIN 0xFFDFFFFF

#define FIO0DIR (*(unsigned int *)0x2009C000)	//GPIO direction
#define FIO0SET (*(unsigned int *)0x2009C018)	//GPIO set (can make pin high)
#define FIO0CLR (*(unsigned int *)0x2009C01C)	//GPIO clear (can make pin low)
#define FIO0PIN (*(unsigned int *)0x2009C014)	//GPIO value (can read and write pin) (write careful! Will effect whole port)

#define T0 0x40004000				//timer0
#define T0IR (*(int *)(T0))			//Interrupt register
#define T0CR (*(int *)(T0 + 0x04))	//control register
#define T0TC (*(int *)(T0 + 0x08))	//Timer Counter register
#define T0PR (*(int *)(T0 + 0x0C))	//Prescaler
#define T0MR0 (*(int *)(T0 + 0x18))	//Match register 0
#define T0MRC (*(int *)(T0 + 0x14))	//match control register
#define ISER0 (*(int *)(0xE000E100)) //Interrupt Set-Enable Register 0

/*
 * NOTE:
 * To use timer 3/4, you need to enable it.
 * This can be done by setting PCTIM2/3 in the PCONP
 */

unsigned char* data;
int size;

void ledsInit() {
	size = 0;

	//set output pin to output mode
	FIO0DIR |= OUTPUTPIN;

	//set match
	T0MR0 = 25;

	//set prescaler
	T0PR = 100;

	//set timer interupt, autoreset, autostop
	T0MRC |= (T0MRC & ~0x07) | 0x7;

	//enable interupt
	ISER0 |= 0x02;

	//start timer
	T0CR |= 0x01;
}

void TIMER0_IRQHandler() {
	T0IR |= 0x01;
	ledsWrite();
	T0CR |= 0x01;
}

void ledsSetData(unsigned char* buffer, int length) {
	if (size < length) {
		data = buffer;
		size = length;
	} else {
		size = length;
		data = buffer;
	}
}

void ledsWrite() {
	for (int i = 0; i < size; ++i) {
		int line = data[i];
		for (int j = 0; j < 8; ++j) {
			FIO0PIN |= OUTPUTPIN;
			if (line & 0x1) {
				//about 480ns
				for (int time = 0; time < 8; ++time) {
					asm("NOP");
				}

				//pin LOW
				FIO0PIN &= NOTOUTPUTPIN;

				//wait LOW time ()
				for (int time = 0; time < 1; ++time) {
					asm("NOP");
				}

				//if last item, reserve some time to go to next item
				if (j < 7) {
					for (int time = 0; time < 3; ++time) {
						asm("NOP");
					}
				} else {
					for (int time = 0; time < 1; ++time) {
					}
				}

			} else {
				//TODO: fine tune
				for (int time = 0; time < 3; ++time) {
					asm("NOP");
				}

				FIO0PIN &= NOTOUTPUTPIN;

				//TODO: fine tune
				for (int time = 0; time < 3; ++time) {
					asm("NOP");
				}

				//if last item, reserve some time to go to next item
				if (j < 7) {
					for (int time = 0; time < 3; ++time) {
						asm("NOP");
					}
				} else {
					for (int time = 0; time < 1; ++time) {
					}
				}
			}
			line >>= 1;
		}
	}
}

