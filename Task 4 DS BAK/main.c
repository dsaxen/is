
#include <msp430g2553.h>
#include "switch.h"
#include "uart.h"
#include "scheduler.h"
#include "blink.h"
#include "adc.h"
#include "ports.h"
#include "timer.h"

void main() {

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer // See function above
	P1DIR |= RED_LED;   	//Set LEDs to output direction
  //P1OUT &= ~RED_LED;

  setup_button();
  UART_Init();
	setup_timer();
	configAdc();

	Scheduler_Add_Task(blink, 4, 4);
  Scheduler_Add_Task(adc, 11, 11); //you do not need to read the adc that often, once every second is fine.
	Scheduler_Add_Task(isPressed, 5, 5); //task, delay, period

	__enable_interrupt(); //Globally enable interrupts

	for(;;) {
		Scheduler_Dispatch_Tasks();
	}
}
__attribute__((interrupt(TIMER0_A0_VECTOR))) void Timer_A(void){ //run scheduler update at interrupt
		Scheduler_Update();
}
