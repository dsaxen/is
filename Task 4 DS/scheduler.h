#define SCHEDULER_MAX_TASKS 5

typedef unsigned char tByte;

typedef unsigned char tWord;


void Scheduler_Init();
void Scheduler_Start();
void Scheduler_Delete_Task(const tByte TASK_INDEX);
void Scheduler_Dispatch_Tasks(void);
tByte Scheduler_Add_Task(void (* pFunction) (), const tWord DELAY, const tWord PERIOD);
void Scheduler_Dispatch_Tasks(void);
void Scheduler_Delete_Task(const tByte TASK_INDEX);
void Scheduler_Sleep();
void Scheduler_Update(void);


typedef struct data{

	void (*pTask) (void); //pointer to the task

	tWord Delay; //delay until the function will be run

	tWord Period; //Interval between subsequent runs

	tByte RunMe; //Incremented by scheduler when task is due to execute
} sTask;
sTask SCH_tasks_G[SCHEDULER_MAX_TASKS];
