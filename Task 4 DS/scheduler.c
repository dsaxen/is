#include <msp430g2553.h>
#include <stdio.h>
#include "scheduler.h"
#include "blink.h"
#include "adc.h"
#include "uart.h"
#include "ports.h"

void Scheduler_Init(){

	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;
	CCTL0 = CCIE;
	TACTL = TASSEL_1 + MC_2 + ID_3;
	CCR0 = TMRC;
	UART_Write("SCH_init OK!\n");
}

void Scheduler_Start(){
	__enable_interrupt();
}
int Scheduler_Add_Task(void (* pFunction) (void), const int DELAY, const int PERIOD){
	UART_Write("Add_task...\n");
	static int Index = 0;
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCHEDULER_MAX_TASKS)){ // Find a gap in the array
		Index++;
	}
	if (Index == SCHEDULER_MAX_TASKS){ //if task list is full
		return SCHEDULER_MAX_TASKS; //return an error code;
	}
	//If we are here there is a space in the task array
	SCH_tasks_G[Index].pTask = pFunction; //add function to scheduler
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;

	UART_Write("Add_task OK\n");
	return Index; //return position of task
}

void Scheduler_Dispatch_Tasks(void){
	static int Index;
	UART_Write("Dispatching tasks...\n");

	for (Index = 0; Index < SCHEDULER_MAX_TASKS; Index++){
		if(SCH_tasks_G[Index].RunMe > 0){

			//Run task
			(*SCH_tasks_G[Index].pTask) ();

			//RunMe = false (RunMe--;)
			SCH_tasks_G[Index].RunMe -= 1;
		}
	}

	UART_Write("Successfully dispatched tasks!\n");
	Scheduler_Sleep(); //enter idle mode
}

void Scheduler_Delete_Task(const int TASK_INDEX){
	UART_Write("Del task...\n");
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000; //reset values
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	UART_Write("Del_task OK!\n");
}

void Scheduler_Sleep(){
	_BIS_SR(LPM1_bits + GIE);
}


void Scheduler_Update(void){
		static int Index;
		for (Index = 0; Index <SCHEDULER_MAX_TASKS; Index++){
			if (SCH_tasks_G[Index].pTask) {
				char strOlle[15];
				sprintf(strOlle, "%d", SCH_tasks_G[Index].RunMe);
				UART_Write("RunMe:");
				UART_Write(strOlle);
				UART_Write("\n");
				if(SCH_tasks_G[Index].RunMe == 8){
						UART_Write("LOL\n");
				}
				if (--SCH_tasks_G[Index].Delay == 0) {
					SCH_tasks_G[Index].RunMe += 1; //include runme flag..

					if (SCH_tasks_G[Index].Period){
						SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
					}
				}
			}
	}
}
