/*
 * magnets.c
 *
 *  Created on: 10 okt. 2016
 *      Author: Acer
 */
#define MAGNET0 0x00400000

#define FIO0DIR (*(unsigned int *)0x2009C000)	//GPIO direction
#define FIO0SET (*(unsigned int *)0x2009C018)	//GPIO set (can make pin high)
#define FIO0CLR (*(unsigned int *)0x2009C01C)	//GPIO clear (can make pin low)
#define FIO0PIN (*(unsigned int *)0x2009C014) 	//GPIO value (can read and write pin) (write careful! Will effect whole port)
#define IO0IntEnR (*(unsigned int *)0x40028090)	//GPIO interrupt set rising edge
#define IO0IntClr (*(unsigned int *)0x4002808C)	//GPIO interupt clear
#define ISER0  (*(unsigned int *)0xE000E100)	//Interrupt set-enable register

void magnet0Init() {
	//set direction
	FIO0DIR &= ~MAGNET0;
	FIO0DIR |= 0x00200000;	//set pin 21 to output

	//interrupt on rising edge
	IO0IntEnR |= MAGNET0;

	//enable external interrupt 3 (for gpio)
	ISER0 |= 0x200000; //bit 21
}

void EINT3_IRQHandler() {
	FIO0PIN ^= 0x00200000;

	IO0IntClr |= MAGNET0;
}
