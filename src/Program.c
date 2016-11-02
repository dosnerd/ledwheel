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
#include "images.h"
#include "timer.h"

void clear(unsigned char *);

int main(void) {
	int line = 0;
	int counter = 0;
	int line2 = 0;
	int counter2 = 0;

	unsigned char dataLine[288];
	unsigned char *pDataline = dataLine; //&dataLine give warning, &pDataline will not
	IMAGE_DATA imageMemory;
	IMAGE_DATA imageData;

	//set properties, so it can be used in interrupts without global variables
	propertySelectLine2(&line2);
	propertySelectLine(&line);
	propertyLine(&pDataline);
	propertyCurrentImage(&imageMemory);

	//set GPU clock higher
	SpeedUp();

	//initialize modules
	timeRecorderInit(500);
	timingInit(500);
	timer2Init();
	magnet0Init();
	ledsInit();

	//turn off all leds
	clear(dataLine);

	//start record timer and update timer with a standard value
	timingSetMatch(10000);

	//start timers
	timeRecorderStart();
	timingStart();
	timer2Start();

	while (1) {
		//save current image, so image doesn't change while loading it to the strips
		imageData = getCurrentImage();

		//when new line needs to be loaded
		if (line != counter) {
			//save value in separate variable, so in line change, counter doens't
			counter = line;
			counter2 = line2;

			//load both strips
			for (int i = 0; i < 48; ++i) {
				//three colors
				for (int j = 0; j < 3; ++j) {
					//load strip 1
					if (line < 96) {
						dataLine[i * 3 + j] = imageData.image[i * 96 * 3
								+ counter * 3 + j];
					} else {
						dataLine[i * 3 + j] = 0;
					}

					//load strip 2
					if (line2 < 96) {
						dataLine[(i + 48) * 3 + j] = imageData.image[i * 96 * 3
								+ counter2 * 3 + j];
					} else {
						dataLine[(i + 48) * 3 + j] = 0;
					}

				}
			}

		}
	}
}

void clear(unsigned char * temp) {
	for (int i = 0; i < 48 * 2 * 3; ++i) {
		temp[i] = 0;
	}
	ledsSetData(temp, (48 * 2) * 3);
}

