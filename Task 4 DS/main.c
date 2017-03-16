
#include <msp430g2553.h>
//#include "timer.h"
#include "switch.h"
#include "uart.h"
#include "scheduler.h"
#include "blink.h"
#include "adc.h"
#include "ports.h"

int main() {

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR |= RED_LED;   	//Set LEDs to output direction
  //P1OUT &= ~RED_LED;

	UART_Init();
  setup_button();

	//Scheduler
	UART_Write("Initializing Scheduler\n");
  Scheduler_Init();
  Scheduler_Add_Task(isPressed, 50, 20);
	Scheduler_Add_Task(adc, 100, 100);
	Scheduler_Add_Task(blink, 100, 200);
	UART_Write("Starting Scheduler\n");

	Scheduler_Start();

	while(1) {
		UART_Write("DIS\n");
		Scheduler_Dispatch_Tasks();
	}
	return 0;
}
__attribute__((interrupt(TIMER0_A0_VECTOR))) void Timer_A(void){ //run scheduler update at interrupt
	Scheduler_Update();
}
