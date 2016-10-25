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
#include "magnets.h"
#include <leds.h>

#define LEDHIGH 255

void setLed(char, char, char, unsigned char *, unsigned int *, int);

int main(void) {
	char lijn = 0;
	//set GPU clock higher
	SpeedUp();

	propertySelectLine(&lijn);
	magnet0Init();
	ledsInit();

	//unsigned char temp[] = { 0, 0, 0, 0, 0, 0, 255, 255, 255};
	unsigned char temp[(48 * 2) * 3];
	unsigned int counter = 0;
	for (int i = 0; i < (48 * 2) * 3; ++i) {
		temp[i] = 0;
	}

	temp[0] = 0;

	while (1) {
		if (lijn) {
			setLed(LEDHIGH, 0, 0, temp, &counter, 48 * 2 * 3);
			setLed(LEDHIGH, LEDHIGH, LEDHIGH, temp, &counter, 48 * 2 * 3);
			setLed(0, 0, LEDHIGH, temp, &counter, 48 * 2 * 3);

			ledsSetData(temp, (48 * 2) * 3);

			if (counter == 0) {
				counter = (48 * 2 * 3) - 1;
			}

			counter -= 9;
			setLed(0, 0, 0, temp, &counter, 48 * 2 * 3);
			setLed(0, 0, 0, temp, &counter, 48 * 2 * 3);
			setLed(0, 0, 0, temp, &counter, 48 * 2 * 3);

			for (int time = 0; time < 100000; ++time) {
				asm("nop");
			}
		}
	}
}

void setLed(char r, char g, char b, unsigned char * array,
		unsigned int *counter, int size) {
	if (*counter >= size) {
		*counter = 0;
	}

	array[*counter] = g;
	array[*counter + 1] = r;
	array[*counter + 2] = b;
	*counter += 3;

	if (*counter >= size) {
		*counter = 0;
	}
}

