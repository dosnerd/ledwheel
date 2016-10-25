/*
 * magnets.c
 *
 *  Created on: 10 okt. 2016
 *      Author: Acer
 */
#define MAGNET0 0x40
#define MAGNET1 0x80

//48, 53

#define FI20DIR (*(unsigned int *)0x2009C040)	//GPIO direction
#define FIO2SET (*(unsigned int *)0x2009C058)	//GPIO set (can make pin high)
#define FIO2CLR (*(unsigned int *)0x2009C05C)	//GPIO clear (can make pin low)
#define FIO2PIN (*(unsigned int *)0x2009C054) //GPIO value (can read and write pin) (write careful! Will effect whole port)#define IO0IntEnR (*(unsigned int *)0x40028090)	//GPIO interrupt set rising edge
#define IO2IntEnR  (*(unsigned int *)0x400280B0)
#define IO2IntClr (*(unsigned int *)0x400280AC)	//GPIO interupt clear
#define ISER0  (*(unsigned int *)0xE000E100)	//Interrupt set-enable register

void magnet0Init() {
	//set direction
	FI20DIR &= ~MAGNET0;
	FI20DIR &= ~MAGNET1;
	FI20DIR |= 0x00200000;	//set pin 21 to output

	//interrupt on rising edge
	IO2IntEnR |= MAGNET0;
	IO2IntEnR |= MAGNET1;

	//enable external interrupt 3 (for gpio)
	ISER0 |= 0x200000; //bit 21
}

void EINT3_IRQHandler() {
	IO2IntClr |= MAGNET0;
	IO2IntClr |= MAGNET1;
	FIO2PIN ^= 0x800;
}
