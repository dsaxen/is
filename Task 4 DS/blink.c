#include "ports.h"
#include <msp430g2553.h>
#include "uart.h"
#include "scheduler.h"
int i = 0;

void blink(void){
	  UART_Write("BLINKING");
		P1OUT ^= RED_LED; //blink red led

}

void isPressed(void){

  if ((~P1IN & BUTTON) == BUTTON){ //if button is pressed
		Scheduler_Delete_Task(2);
/*		int k = 0;

		for(i=0; i<2; i++){
			if (SCH_tasks_G[i].Delay == 4){ //if there is a task for blinking
					Scheduler_Delete_Task(i); //remove the task
					k = 1;
			}
		}
		i = 0;
		if (k == 0){ //if there is not task for blinking
				Scheduler_Add_Task(blink,4,5);//add it
		}
*/
    }

}
