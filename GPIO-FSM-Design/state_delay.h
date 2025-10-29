/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the main  header file used to add a 5 second transition time between every state transition
* 
*/
#ifndef STATE_DELAY_H
#define STATE_DELAY_H

#include <stdint.h>

// Call once at startup (after timer0_init)
void state_delay_init(void);

// Busy-wait exactly `seconds` seconds
void state_delay_wait(uint32_t seconds);

#endif
