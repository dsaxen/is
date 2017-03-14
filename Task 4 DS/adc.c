#include <msp430g2553.h>
#include "uart.h"
#include "stdio.h"
#include "adc.h"
#include "ports.h"

static int ADC_value = 0;
static int temperature = 0;

void configAdc(void){
	ADC10CTL1 = INCH_10 + ADC10DIV_3 ;         // Channel 10 is the temperature sensor, ADC10CLK/0
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, REF on
	ADC10CTL0 |= ENC + ADC10SC;
}

void adc(void)
{
			__delay_cycles(50); //allow time for ref to settle
			char strTemp[15];


			ADC10CTL0 |= ENC + ADC10SC;			// Sampling and conversion start

			ADC_value = ADC10MEM;				// Assigns the value held in ADC10MEM to the integer called ADC_value

			temperature = ((ADC_value - 673) * 423) / 1024; //conversion to celsius
			sprintf(strTemp, "%d", temperature);	//conversion to string

			UART_Write("Current temperature in Celsius: ");
			UART_Write(strTemp); //keep your finger on the microcontroller to see the difference on PuTtY.
			UART_Write("\n");


			__delay_cycles(100);
}
