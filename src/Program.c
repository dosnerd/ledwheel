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
#include "timing.h"
#include "timeRecorder.h"
#include "magnets.h"
#include "leds.h"
#include "avans.h"

void clear(void);

int main(void) {
	int line = 0;
	int counter = 0;
	//unsigned char image[96 * 96 * 3];
	unsigned char dataLine[288];
	unsigned char *pDataline = dataLine; //&dataLine give warning, &pDataline will not

	//set properties
	propertySelectLine(&line);
	propertyLine(&pDataline);
	//set GPU clock higher
	SpeedUp();

	timeRecorderInit(500);
	timingInit(500);
	magnet0Init();
	ledsInit();

	//turn off all leds
	clear();

	//start record timer and update timer with a standard value
	timeRecorderStart();
	timingSetMatch(10000);
	timingStart();

	while (1) {
		//when new line needs to be loaded
		if (line != counter) {
			if (line < 96) {
				counter = line;
				int bottomLine = (counter + 48) % 96;
				for (int i = 0; i < 48; ++i) {
					//three colors
					for (int j = 0; j < 3; ++j) {
						dataLine[i * 3 + j] =
								image[i * 96 * 3 + counter * 3 + j];
						dataLine[(i + 48) * 3 + j] =
								0;
								//image[i * 96 * 3 + bottomLine * 3 + j];
					}
				}
			} else {
				line = counter;
			}
		}
	}
}

void clear() {
	unsigned char temp[48 * 2 * 3];
	//for (int i = 0; i < (48 * 2) * 3; ++i) {
	for (int i = 0; i < 48 * 2 * 3; ++i) {
		temp[i] = 0;
	}
	ledsSetData(temp, (48 * 2) * 3);
}

