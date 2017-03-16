//ADC.c
//Fixad med hjälp av Anton Lindholm

#include <msp430g2553.h>
#include "uart.h"

static unsigned int lastTemp = 0;
static unsigned int currTemp = 0;
static unsigned int deg = 0;

void init_ADC(void) {
	UART_Write("Yo dog, ADC is here!\n");

	P1SEL |= BIT3;
	ADC10CTL1 = INCH_3 + ADC10DIV_3;
	ADC10CTL1 = SREF_0 + ADC10SHT_3 + ADC10ON;
	ADC10AE0 |= BIT3;
	ADC10CTL0 |= ENC + ADC10SC;
}

void calc_temp(void){
	temp = ADC10MEM;
	__delay_cycles(1000);
	ADC10CTL0 |= ENC + ADC10SC;
	deg = ((temp - 673) * 423) /1024;
	if (deg > lastTemp) {
		P1OUT ^= GREEN_LED;
		gBLINK_PERIOD = 5;
		lastTemp = deg;
	} else {
		P1OUT &= ~GREEN_LED;

	}
}
/*
void adc(void) {
			UART_Write("ADC()\n");
			ADC10CTL1 = INCH_10 + ADC10DIV_0 ;         // Channel 10 is the temperature sensor, ADC10CLK/0
			ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on
			__delay_cycles(500); //allow time for ref to settle

			int temperature = 0;
			char strTemp[15];
			ADC10CTL0 |= ENC + ADC10SC;			// Sampling and conversion start
			__delay_cycles(50);
			ADC10CTL0&=~ENC; 					//disable conversion
			ADC10CTL0&= ~(REFON + ADC10ON); 		//disable ADC and ref

			ADC_value = ADC10MEM;				// Assigns the value held in ADC10MEM to the integer called ADC_value

			temperature= ((ADC_value * 27069L - 18169625L) >> 16); //conversion to celsius
			sprintf(strTemp, "%d", temperature);	//conversion to string

			UART_Write("Temp: ");
			UART_Write(strTemp); //keep your finger on the microcontroller to see the difference on PUTty.
			UART_Write("\n");
}
*/
