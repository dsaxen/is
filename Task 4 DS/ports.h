#include <msp430g2553.h>

#define RED_LED 0x01
#define GREEN_LED 0x40
#define BUTTON 0x08
#define LEDSON 0x41

#define DCO_FREQ 1*1e6
#define TIMER_INTERVAL 50 //given in ms

#define DIVIDER 8
#define TMRC (DCO_FREQ / DIVIDER / 1000 * TIMER_INTERVAL)

