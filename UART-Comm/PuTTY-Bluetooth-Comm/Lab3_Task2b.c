/*
* Pranav Ananthram
* 2122059
* 5/16/2025
*This is the main file for Lab 3 task 2b and is used to send and read a single character through  UART to putty interfance
* to perform a return to sender function
*/
/**
 * EE/CSE 474: Lab3 Task1b main function
 */

// NOTE: This is the main function for Task 1b. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "Lab3_2b_Inits.h"
#include "lab3-2b.h"
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

   
int main(void) {
   
  PLL_Init(PRESET2); 
    UART3_Init();           // Set up UART3 (PA4 = RX, PA5 = TX)

    while (1) {
        char c = UART3_ReadChar();  // Receive from PuTTY
        UART3_WriteChar(c);         // Echo back to PuTTY
    }
    
    return 0;
}



