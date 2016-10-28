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
#include "timing2.h"
#include "timeRecorder.h"
#include "magnets.h"
#include "leds.h"
#include "avans.h"

void clear(unsigned char *);

int main(void) {
	int line = 0;
	int counter = 0;

	int line2 = 0;
	int counter2 = 0;

	//unsigned char image[96 * 96 * 3];
	unsigned char dataLine[288];
	unsigned char *pDataline = dataLine; //&dataLine give warning, &pDataline will not

	//set properties
	propertySelectLine2(&line2);
	propertySelectLine(&line);
	propertyLine(&pDataline);

	//set GPU clock higher
	SpeedUp();

	timeRecorderInit(500);
	timingInit(500);
	timing2Init(500);
	magnet0Init();
	ledsInit();

	//turn off all leds
	clear(dataLine);

	//start record timer and update timer with a standard value
	timingSetMatch(10000);
	timing2SetMatch(10000);

	timeRecorderStart();
	timingStart();
	timing2Start();

	while (1) {
		//when new line needs to be loaded
		if (line != counter) {
			if (line < 96) {
				counter = line;
				//int bottomLine = (counter + 48) % 96;
				for (int i = 0; i < 48; ++i) {
					//three colors
					for (int j = 0; j < 3; ++j) {
						dataLine[i * 3 + j] =
								image[i * 96 * 3 + counter * 3 + j];
						/*dataLine[(i + 48) * 3 + j] =
						 0;*/
						//image[i * 96 * 3 + bottomLine * 3 + j];
					}
				}
			} else {
				for (int i = 0; i < 48; ++i) {
					//three colors
					for (int j = 0; j < 3; ++j) {
						dataLine[(i + 48) * 3 + j] = image[i * 96 * 3 + 94 * 3
								+ j];
					}
				}
				line = counter;
			}
		}

		//when new line needs to be loaded
		if (line2 != counter2) {
			if (line2 < 96) {
				counter2 = line2;
				for (int i = 0; i < 48; ++i) {
					//three colors
					for (int j = 0; j < 3; ++j) {
						dataLine[(i + 48) * 3 + j] = image[i * 96 * 3
								+ counter2 * 3 + j];
					}
				}
			} else {
				for (int i = 0; i < 48; ++i) {
					//three colors
					for (int j = 0; j < 3; ++j) {
						dataLine[(i + 48) * 3 + j] = image[i * 96 * 3 + 94 * 3
								+ j];
					}
				}
				timing2Stop();
			}
		}
	}
}

void clear(unsigned char * temp) {
	//unsigned char temp[48 * 2 * 3];
	//for (int i = 0; i < (48 * 2) * 3; ++i) {
	for (int i = 0; i < 48 * 2 * 3; ++i) {
		temp[i] = 0;
	}
	ledsSetData(temp, (48 * 2) * 3);
}

