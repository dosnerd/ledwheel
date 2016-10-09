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
#include <leds.h>

int main(void) {
	//set GPU clock higher
	SpeedUp();

	ledsInit();

	unsigned char temp[] = { 255, 0, 255, 255, 0, 255 };

	while (1) {
		ledsSetData(temp, 6);
		/*for (int i = 0; i < 6; ++i) {
			temp[i]++;
		}*/

		for (int time = 0; time < 10000000; ++time) {
			asm("nop");
		}
	}
}
