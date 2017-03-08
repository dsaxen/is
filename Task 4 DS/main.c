
#include <msp430g2553.h>
#include "setup.h"
#include "timer.h"
#include "scheduler.h"

int main() {

	setupSystem();
	__enable_interrupt();


	while(1) {
		Scheduler_Dispatch_Tasks();
	}

	return 0;
}
__attribute__((interrupt(TIMER0_A0_VECTOR))) void Timer_A(void){ //run scheduler update at interrupt
	Scheduler_Update();
}
