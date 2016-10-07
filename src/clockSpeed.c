/*
 * clock.c
 *
 *  Created on: 5 okt. 2016
 *      Author: Acer
 */

#define PLL0FEED (*(unsigned int*)(0x400fC08C))		//feed (security)
#define PLL0CON (*(unsigned int*)(0x400FC080))		//config (on/off, dis-/enable)
#define CCLKCFG (*(unsigned int*)(0x400FC104))		//clock devider
#define CLKSRCSEL (*(unsigned int*)(0x400FC10C))	//clock source select
#define PLL0CFG (*(unsigned int*)(0x400FC084))
#define SCS (*(unsigned int*)(0x400FC1A0))
#define PLL0STAT (*(unsigned int*)(0x400FC088))

//36, 47

//8100
//1
void PLL0FeedSeq() {
	unsigned char restricted = PLL0FEED & ~0xFF;
	PLL0FEED = restricted | 0xAA;
	PLL0FEED = restricted | 0x55;
}

void SpeedUp() {
	//setup main oscillator
	SCS |= 0x30;

	//wait until oscillator is ready
	while ((SCS & 0x40) == 0) {
		asm("NOP");
	}

	//page 47

	//1. disconnect PLL0
	PLL0CON &= ~0x2;
	PLL0FeedSeq();

	//2. disable PLL0
	PLL0CON &= ~0x1;
	PLL0FeedSeq();

	//3. set clock devider
	//CCLKCFG &= ~254;

	//4. Clock Source Selection Control
	CLKSRCSEL = (CLKSRCSEL & ~0x3) | 0x1;

	//5. Setup PLL0CFG
	unsigned int PLL0CFGrestricted = PLL0CFG & ~0xF8008000;
	//PLL0CFG = PLL0CFGrestricted | 4395 | 0x10000;
	PLL0CFG = PLL0CFGrestricted | 10 | 0x10000;
	PLL0FeedSeq();

	//6. enable PLL
	PLL0CON |= 1;
	PLL0FeedSeq();

	//7. set clock devider
	CCLKCFG &= ~(255-0);

	//8. wait until PLL0 is ready
	//wait more then 500us
	for (unsigned int i = 0; i < 429000; ++i) {
		asm("NOP");
	}

	while((PLL0STAT & 0x4000000) == 0){
		asm("NOP");
	}

	//9. connect PLL0
	PLL0CON |= 0x2;
	PLL0FeedSeq();
}
