#include "ports.h"
#include <msp430g2553.h>
#include "uart.h"
#include "scheduler.h"

void blink(void){
		P1OUT ^= RED_LED; //blink red led
}

void isPressed(void){

  if ((~P1IN & BUTTON) == BUTTON){ //if button is pressed

		if (Scheduler_Add_Task(blink,4,5) == 3){ //there is a task for blinking
				Scheduler_Delete_Task(3); //remove the task
		}
		else{
			Scheduler_Add_Task(blink,4,5);//add it
		}

  }
}
