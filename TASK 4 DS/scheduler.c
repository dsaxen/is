#include <msp430g2553.h>
#include "scheduler.h"
#include "blink.h"
#include "adc.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>
#include "ports.h"

static int ticks = 0;
static int Index = 0;
sTask SCH_tasks_G[SCHEDULER_MAX_TASKS];

void Scheduler_Add_Task(void (*pFunction) (void), int DELAY, int PERIOD){

	//If we are here there is a space in the task array
	SCH_tasks_G[Index].pTask = pFunction; //add function to scheduler

	SCH_tasks_G[Index].Delay = DELAY + 1;
	SCH_tasks_G[Index].Period = PERIOD;
	Index++;
}
void Scheduler_Faster_Period(int TASK_INDEX, int temperature){ //blink faster
			char strTemp[15];
			sprintf(strTemp, "%d", temperature);	//conversion to string
			UART_Write(strTemp);
			SCH_tasks_G[TASK_INDEX].Period = 4;
			SCH_tasks_G[TASK_INDEX].Delay = 4;
}
void Scheduler_Slower_Period(int TASK_INDEX, int temperature){//blink slower
			char strTemp[15];
			sprintf(strTemp, "%d", temperature);	//conversion to string
			UART_Write(strTemp);
			SCH_tasks_G[TASK_INDEX].Period = 14;
			SCH_tasks_G[TASK_INDEX].Delay = 14;
}

void Scheduler_Dispatch_Tasks(void){
	__disable_interrupt();
	if(ticks>0){ //when update has been run
		for (int i=0; i<Index; i++){
			if (--SCH_tasks_G[i].Delay == 0){
					SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;

					__enable_interrupt();
					SCH_tasks_G[i].pTask(); //running the tasks
					__disable_interrupt();
			}
		}
		ticks--; //reduce tick count
	}
	__enable_interrupt();
}
void Scheduler_Delete_Task(int TASK_INDEX){
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000; //reset values
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
}
void Scheduler_Update(void){
	ticks++;
}
