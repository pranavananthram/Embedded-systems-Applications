/*
* Pranav Ananthram
* 2122059
* 4/17/2025
* This is the main file for task 1 part B. In this file, we are initializing port N and J to switch on their respected LEDs using user switches. We establish PN0 and PN1 as outputs and PJ0 and PJ1 as inputs
* And then by using conditional logic to switch on PN1 and PN0 when PJ1 and PJ0 are 1 respectively we are able to switch on the LEDs as long as the user holds the switch.
*/
// Defining partBtaskone header file to use Port J and N and additional library.
#include <stdint.h>
#include "partBtaskone.h"

int main(void)
{
    volatile unsigned short delay = 0;
    int j;

    RCGCGPIO |= 0x1100; // Enable Port N and Port J clocks 

    delay++;
    delay++;
 
    GPIODIR_N = 0x03; // PN0 and PN1 as outputs
    GPIODEN_N = 0x03; // Enable PN0 and PN1
    
    GPIODIR_J &= ~0x03;    // PJ0 and PJ1 as inputs
    GPIODEN_J |= 0x03;     // Enable PJ0 and PJ1

   
    GPIOPUR_J |= 0x03;      // Enable pull-up resistors on PJ0 and PJ1
   while (1) 
{
    if ((GPIODATA_J & 0x01) == 0) {
      GPIODATA_N |= 0x02; // Turn on PN1 
       for (j = 0; j < 1000000; j++);
    }
    if ((GPIODATA_J & 0x02) == 0) {     
      GPIODATA_N = 0x01; // Turn on PN0 
       for (j = 0; j < 1000000; j++);
    }
    else {
      GPIODATA_N = 0x00; // Turn off PN0 and PN1
    }
}
    return 0;
}