#include "timer.h"
#include <msp430g2553.h>
#include "ports.h"

void init_timer(void){
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  CCTL0 = CCIE;
  TACTL = TASSEL_2 + MC_1 + ID_3;
  CCR0 = TMRC; //TMRC is defined in ports.h
}
