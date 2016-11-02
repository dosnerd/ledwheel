/*
 * timer1.c
 *
 *  Created on: 6 okt. 2016
 *      Author: Acer
 */
#define OUTPUTPIN 0x00000080
#define NOTOUTPUTPIN 0xFFFFFF7F

#define FIO0DIR (*(unsigned int *)0x2009C040)	//GPIO direction
#define FIO0SET (*(unsigned int *)0x2009C058)	//GPIO set (can make pin high)
#define FIO0CLR (*(unsigned int *)0x2009C05C)	//GPIO clear (can make pin low)
#define FIO0PIN (*(unsigned int *)0x2009C054)	//GPIO value (can read and write pin) (write careful! Will effect whole port)

#define T0 0x40004000				//timer0
#define T1IR (*(int *)(T0))			//Interrupt register
#define T1CR (*(int *)(T0 + 0x04))	//control register
#define T1TC (*(int *)(T0 + 0x08))	//Timer Counter register
#define T1PR (*(int *)(T0 + 0x0C))	//Prescaler
#define T1MR0 (*(int *)(T0 + 0x18))	//Match register 0
#define T1MRC (*(int *)(T0 + 0x14))	//match control register
#define ISER0 (*(int *)(0xE000E100)) //Interrupt Set-Enable Register 0

/*
 * NOTE:
 * To use timer 3/4, you need to enable it.
 * This can be done by setting PCTIM2/3 in the PCONP
 */

void ledsInit() {
	//size = 0;

	//set output pin to output mode
	FIO0DIR |= OUTPUTPIN;
}

void ledsSetData(unsigned char* data, int size) {
	int top = size / 2;

	for (int i = 0; i < 288; i += 3) {
		if (i < 48 * 3) {
			unsigned char temp = data[i];
			data[i] = data[i + 1];
			data[i + 1] = temp;
		} else {
			unsigned char r = data[i];
			unsigned char g = data[i + 1];
			unsigned char b = data[i + 2];

			data[i] = b;
			data[i + 1] = r;
			data[i + 2] = g;
		}
	}

	//top
	for (int i = 0; i < top; ++i) {
		int line = data[i];
		for (int j = 0; j < 8; ++j) {
			FIO0PIN &= NOTOUTPUTPIN;
			if (line & 0x1) {
				//about 480ns
				for (int time = 0; time < 7; ++time) {
					asm("NOP");
					asm("NOP");
				}

				//pin LOW
				FIO0PIN |= OUTPUTPIN;

				//if last item, reserve some time to go to next item
				if (j < 7) {
					for (int time = 0; time < 1; ++time) {
						asm("NOP");
					}
				} else {
//					for (int time = 0; time < 0; ++time) {
//					}
				}

			} else {
				for (int time = 0; time < 2; ++time) {
					asm("NOP");
				}

				FIO0PIN |= OUTPUTPIN;

				for (int time = 0; time < 2; ++time) {
					asm("NOP");
				}

				//if last item, reserve some time to go to next item
				if (j < 7) {
					for (int time = 0; time < 3; ++time) {
						asm("NOP");
					}
				} else {
					for (int time = 0; time < 0; ++time) {
					}
				}
			}
			line >>= 1;
		}
	}

	//bottom
	for (int i = size - 1; i >= top; --i) {
		int line = data[i];
		for (int j = 0; j < 8; ++j) {
			FIO0PIN &= NOTOUTPUTPIN;
			if (line & 0x1) {
				//about 480ns
				for (int time = 0; time < 7; ++time) {
					asm("NOP");
					asm("NOP");
				}

				//pin LOW
				FIO0PIN |= OUTPUTPIN;

				//if last item, reserve some time to go to next item
				if (j < 7) {
					for (int time = 0; time < 1; ++time) {
						asm("NOP");
					}
				} else {
					//					for (int time = 0; time < 0; ++time) {
					//					}
				}

			} else {
				for (int time = 0; time < 2; ++time) {
					asm("NOP");
				}

				FIO0PIN |= OUTPUTPIN;

				for (int time = 0; time < 2; ++time) {
					asm("NOP");
				}

				//if last item, reserve some time to go to next item
				if (j < 7) {
					for (int time = 0; time < 3; ++time) {
						asm("NOP");
					}
				} else {
					for (int time = 0; time < 0; ++time) {
					}
				}
			}
			line >>= 1;
		}
	}
}

