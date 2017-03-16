#include "ports.h"
#include <msp430g2553.h>
#include "uart.h"

void blink(void){
	  UART_Write("BLINK()\n");
		P1OUT ^= RED_LED; //blink red led
}
