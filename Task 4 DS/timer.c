
#include"ports.h"
#include "blink.h"
#include<msp430g2553.h>

void setup_timer(void){

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 = 0x0;

	//Enable interrupts
	CCTL0 = CCIE;


	TACTL = TASSEL_2 + MC_1 + ID_3;

	CCR0 = TMRC; //TMRC is defined in ports.h
}
