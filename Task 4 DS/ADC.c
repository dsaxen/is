
#include "msp430g2553.h"
#include "uart.h"
#include "stdio.h"
volatile int ADC_value;



void adc(void)
{
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
			
			UART_Write("Current temperature in Celsius: ");
			UART_Write(strTemp); //keep your finger on the microcontroller to see the difference on PUTty.
			UART_Write("\n");
			
			__delay_cycles(100000);
}
