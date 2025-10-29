/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the main file for hold button and is used to allow other functions to check if the button is pressed for 2 sec. .
* 
*/
#include "hold_button.h"
#include "button.h"        // switch_input()
#include "timer_utils.h"   // timer0_wait_ms()

void hold_button_init(void) {
    
}

uint8_t button_held_2s(uint8_t pin) {
    // if button isn’t even pressed, bail out immediately
    if (!switch_input(pin)) return 0;
    // otherwise wait 2000 ms
    timer0_wait_ms(2000);
    // then check again
    return switch_input(pin) ? 1 : 0;
}
