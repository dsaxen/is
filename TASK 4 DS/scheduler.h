#define SCHEDULER_MAX_TASKS 3

void Scheduler_Delete_Task(int TASK_INDEX);
void Scheduler_Dispatch_Tasks(void);
void Scheduler_Add_Task(void (*pFunction)(), int DELAY, int PERIOD);
void Scheduler_Update(void);
void Scheduler_Faster_Period(int TASK_INDEX, int temperature);
void Scheduler_Slower_Period(int TASK_INDEX, int temperature);

typedef struct data{

	void (*pTask) (void); //pointer to the task

	int Delay; //delay until the function will be run

	int Period; //Interval between subsequent runs

} sTask;
