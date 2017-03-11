
#include <msp430g2553.h>
#include "timer.h"
#include "switch.h"
#include "uart.h"
#include "scheduler.h"
#include "blink.h"
#include "adc.h"
#include "ports.h"

int main() {

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer // See function above
	P1DIR |= RED_LED;   	//Set LEDs to output direction
  //P1OUT &= ~RED_LED;

  setup_button();
  setup_timer();
  UART_Init();
  Scheduler_Init();

  Scheduler_Add_Task(isPressed, 0, 5);
  Scheduler_Add_Task(adc, 18, 18); //you do not need to read the adc that often, once every second is fine.
  Scheduler_Add_Task(blink, 4, 5);

  Scheduler_Start();


	while(1) {
		Scheduler_Dispatch_Tasks();
	}
	return 0;
}
__attribute__((interrupt(TIMER0_A0_VECTOR))) void Timer_A(void){ //run scheduler update at interrupt
	Scheduler_Update();
}
