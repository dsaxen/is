#include <msp430g2553.h>
#include "scheduler.h"



void Scheduler_Init(){
	tByte i;

	for(i = 0; i<SCHEDULER_MAX_TASKS; i++){
		Scheduler_Delete_Task(i);
	}
}
void Scheduler_Start(){
	__enable_interrupt();
}
tByte Scheduler_Add_Task(void (* pFunction) (void), const tWord DELAY, const tWord PERIOD){
	static tByte Index = 0;

	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCHEDULER_MAX_TASKS)){ // Find a gap in the array
		Index++;
	}

	if (Index == SCHEDULER_MAX_TASKS){ //if task list is full
		return SCHEDULER_MAX_TASKS; //return an error code;
	}

	//If we are here there is a space in the task array
	SCH_tasks_G[Index].pTask = pFunction; //add function to scheduler

	SCH_tasks_G[Index].Delay = DELAY + 1;
	SCH_tasks_G[Index].Period = PERIOD;

	SCH_tasks_G[Index].RunMe = 0;

	return Index; //return position of task
}

void Scheduler_Dispatch_Tasks(void){
	static tByte Index;

	for (Index = 0; Index < SCHEDULER_MAX_TASKS; Index++){
		if(SCH_tasks_G[Index].RunMe > 0){
			(*SCH_tasks_G[Index].pTask) (); //run task

			SCH_tasks_G[Index].RunMe -= 1; //Reduce RunMe count

			if (SCH_tasks_G[Index].Period == 0){ //Delete "one shot" tasks
				Scheduler_Delete_Task(Index);
			}
		}

	}

	//Scheduler_Sleep(); //enter idle mode


}
void Scheduler_Delete_Task(const tByte TASK_INDEX){

	SCH_tasks_G[TASK_INDEX].pTask = 0x0000; //reset values
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;

}

void Scheduler_Sleep(){
	_BIS_SR(LPM1_bits + GIE);
}
void Scheduler_Update(void){ //Update the task list
	static tByte Index;

	for (Index = 0; Index <SCHEDULER_MAX_TASKS; Index++){
			if (SCH_tasks_G[Index].pTask){
				if (--SCH_tasks_G[Index].Delay == 0){
					SCH_tasks_G[Index].RunMe += 1;

					if (SCH_tasks_G[Index].Period){
						SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
					}
				}
			}
	}
}
