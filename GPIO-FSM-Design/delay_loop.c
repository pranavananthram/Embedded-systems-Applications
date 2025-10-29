/*
* Pranav Ananthram
* 2122059
* 4/17/2025
* This file is used to add a 0.3 second delay between each state transition and button press to allow the functionality to be percieved by iterating without performing any specific function
*/
// This header file is used to enable this file and allow other functions to call this file.
#include "delay_loop.h"
// Code was provided in lab doc to add a 0.3 second delay so that the code can be percieved in real time.
void delay_loop(void)
{
    volatile unsigned long j;
    for (j = 0; j < 1000000; j++) { // adds a delay of 0.3 second
        
    }
}