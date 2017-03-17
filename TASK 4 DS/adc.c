#include <msp430g2553.h>
#include "uart.h"
#include "adc.h"
#include "ports.h"
#include "scheduler.h"

static int ADC_value = 0;
static int temperature = 0;
static int oldTemp = 0;

void adc(void){

			//ADC10CTL0 &= ~(ENC + ADC10ON);
			ADC10CTL1 = INCH_10 + ADC10DIV_3 ;         // Channel 10 is the temperature sensor, ADC10CLK/0
			ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, REF on
			__delay_cycles(100); //allow time for ref to settle
			char strTemp[15];

			ADC10CTL0 |= ENC + ADC10SC;			// Sampling and conversion start
			__delay_cycles(150);

			ADC10CTL0 &= ~(ENC + ADC10ON);		//stop conversion
			ADC_value = ADC10MEM;				// Assigns the value held in ADC10MEM to the integer called ADC_value

			accessTemp(ADC_value);	 //conversion to celsius

			__delay_cycles(50);
}
void accessTemp(int ADC_value){
		temperature = ((ADC_value * 27069L - 18169625L) >> 16);
		if (temperature > oldTemp){
				Scheduler_Faster_Period(0, temperature); //change period of blink task
		}
		else{
				Scheduler_Slower_Period(0, temperature);
		}
			oldTemp = temperature;
}
