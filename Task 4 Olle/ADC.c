#include <msp430g2553.h>
#include "uart.h"
#include "stdio.h"

//global var
char strTemp[15];

void adc(void)
{
	  UART_Write("Initializing ADC\n");
    volatile int ADC_value=0;
		UART_Write("ADC value set to 0\n");
    volatile int temperature=0;
		UART_Write("temperature set to 0\n");
	  __delay_cycles(1000);				// Wait for ADC Ref to settle
	  UART_Write("Delay cycles 1000\n");
		ADC10CTL0 |= ENC + ADC10SC;			// Sampling and conversion start
	  while(ADC10CTL1 & BUSY);
		UART_Write("ADC10CTL0 set\n");
		__bis_SR_register(CPUOFF + GIE);	// Low Power Mode 0 with interrupts enabled
	  UART_Write("SR register set\n");
		ADC_value = ADC10MEM;				// Assigns the value held in ADC10MEM to the integer called ADC_value
    UART_Write("ADC value set\n");
		temperature = ((ADC_value * 27069L - 18169625L) >> 16); //conversion
    UART_Write("temperature set #2\n");
		ADC10CTL0&=~ENC; //disable conversion
    UART_Write("ADC10CTL0&=~ENC\n");
		sprintf(strTemp, "%d", temperature);
    UART_Write(strTemp);
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
	__bic_SR_register_on_exit(CPUOFF);        // Return to active mode }
}

// Function containing ADC set-up
void ConfigureAdc(void)
{
	UART_Write("Configuring ADC\n");
	ADC10CTL0 = SREF_1 + REFON + ADC10ON + ADC10SHT_3;  // 1.5V ref, REf on, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
  ADC10CTL1 = INCH_10 + ADC10DIV_3 ;         // Channel 10 is the temperature sensor, ADC10CLK/3
	__delay_cycles(1000);
}
