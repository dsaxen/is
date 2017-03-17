#include "ports.h"
#include <msp430g2553.h>

void blink(void){
		if (((~P1IN & BUTTON) == BUTTON)){ //if button is pressed..
			P1OUT &= ~RED_LED;	//stop blinking
		}
		else{	//when button is released...
			P1OUT ^= RED_LED; //blink red led
		}
}
