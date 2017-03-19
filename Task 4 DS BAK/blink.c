#include "ports.h"
#include <msp430g2553.h>
#include "uart.h"
#include "scheduler.h"
#include "adc.h"

void blink(void){
		P1OUT ^= RED_LED; //blink red led
}

void isPressed(void){

  if ((P1IN & BUTTON) == 0){ //if button is pressed
		for (int i = 0; i < SCHEDULER_MAX_TASKS; i++){
			Scheduler_Delete_Task(i);
		}
	}
}
