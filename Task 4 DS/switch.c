
#include <msp430g2553.h>
#include "ports.h"
#include "uart.h"
void init_button(void){
  UART_Write("BUTTON INIT\r\n");
  P1DIR &= ~BUTTON;   // Set button pin as an input pin
  P1OUT |= BUTTON;    // Set pull up resistor on for button
  P1REN |= BUTTON;    // Enable pull up resistor for button to keep pin high until pressed
}
