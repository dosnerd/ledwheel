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

#include <cr_section_macros.h>

#include "clockSpeed.h"

int main(void) {
	//set GPU clock higher
    SpeedUp();
}
