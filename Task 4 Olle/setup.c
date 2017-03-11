#include<msp430g2553.h>

#include "ports.h"
#include "setup.h"
#include "timer.h"
#include "switch.h"
#include "uart.h"
#include "scheduler.h"
#include "blink.h"
#include "ADC.h"

void setupSystem(void){

  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer // See function above
  P1DIR |= RED_LED;   	//Set LEDs to output direction
  P1DIR |= GREEN_LED;
  P1OUT &= ~RED_LED;
  P1OUT &= ~GREEN_LED;
  P1SEL |= BIT3;					// ADC input pin P1.3

  setup_button();
  setup_timer();
  UART_Init();
  Scheduler_Init();
  ConfigureAdc();

  Scheduler_Add_Task(isPressed, 5, 5);
  Scheduler_Add_Task(adc, 5, 10);
    Scheduler_Add_Task(blink, 5, 6); //task, delay until function will be run, interval between subsequent runs

}
