/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the main header file for hold button and is used to allow other functions to check if the button is pressed for 2 sec. .
* 
*/
#ifndef HOLD_BUTTON_H
#define HOLD_BUTTON_H

#include <stdint.h>

// Must be called once after extern_switch_init()
void hold_button_init(void);

// Returns 1 if PL<pin> was held continuously high for 2000 ms, else 0.
// Internally uses timer0_wait_ms().
uint8_t button_held_2s(uint8_t pin);

#endif
