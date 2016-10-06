/*
===============================================================================
 Name        : Program.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

//temp
#define FIO0DIR (*(unsigned int *)0x2009C000)	//GPIO direction
#define FIO0SET (*(unsigned int *)0x2009C018)	//GPIO set (can make pin high)
#define FIO0CLR (*(unsigned int *)0x2009C01C)	//GPIO clear (can make pin low)
#define FIO0PIN (*(unsigned int *)0x2009C014)	//GPIO value (can read and write pin) (write careful! Will effect whole port)

#include <cr_section_macros.h>

#include "clockSpeed.h"
#include "timer0.h"

int main(void) {
	//set GPU clock higher
    SpeedUp();
    //set pin 21 to output
    FIO0DIR |= 1 << 21;

    timer0SetPrescaler0(10);
    timer0SetMatch0(1, 0x03);
    timer0EnableInterrupt();
    timer0Start();


    while(1){

    }
}

void TIMER0_IRQHandler(){
	timer0ResetInterrupt();
	FIO0PIN ^= 1 << 21;
}
