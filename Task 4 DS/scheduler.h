#define SCHEDULER_MAX_TASKS 5

//typedef unsigned char tByte;

//typedef unsigned char tWord;


void Scheduler_Init();
void Scheduler_Start();
void Scheduler_Delete_Task(const int TASK_INDEX);
void Scheduler_Dispatch_Tasks(void);
int Scheduler_Add_Task(void (* pFunction) (), const int DELAY, const int PERIOD);
void Scheduler_Dispatch_Tasks(void);
void Scheduler_Delete_Task(const int TASK_INDEX);
void Scheduler_Sleep();
void Scheduler_Update(void);


typedef struct data{

	void (*pTask) (void); //pointer to the task

	int Delay; //delay until the function will be run

	int Period; //Interval between subsequent runs

	int RunMe; //Incremented by scheduler when task is due to execute
} sTask;
sTask SCH_tasks_G[SCHEDULER_MAX_TASKS];
