/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the main  file used to add a 5 second transition time between every state transition
* 
*/
#include "state_delay.h"
#include "timer_utils.h"  // timer0_wait_seconds()

void state_delay_init(void) {
    // nothing to do—timer already configured
}

void state_delay_wait(uint32_t seconds) {
    timer0_wait_seconds(seconds);
}
