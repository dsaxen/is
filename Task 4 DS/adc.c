#include <msp430g2553.h>
#include "uart.h"
#include "stdio.h"
#include "adc.h"
volatile static int ADC_value = 0;
volatile static int temperature = 0;

void init_ADC(void){
	__delay_cycles(50);
	UART_Write("ADC INIT\r\n");
	ADC10CTL1 = INCH_10 + ADC10DIV_3 ;         // Channel 10 is the temperature sensor, ADC10CLK/0
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, REF off
	ADC10CTL0 |= ENC + ADC10SC;
	__delay_cycles(50);
}

void read_temp(void)
{
			__delay_cycles(50); //allow time for ref to settle
			char strTemp[15];
			ADC10CTL0 |= ENC + ADC10SC;
			ADC_value = ADC10MEM;

			//To celcius
			temperature = ((ADC_value - 673) * 423) / 1024;

			//To string
			sprintf(strTemp, "%d", temperature);

			UART_Write("Temp (C): ");
			UART_Write(strTemp);
			UART_Write("\r\n");

			__delay_cycles(100);
}
