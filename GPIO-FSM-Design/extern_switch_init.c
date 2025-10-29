/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This file is used to enable the external buttons by setting pins PL0 and PL1 to input so that when the button is held and the code registers a digital high it will output 1 else 0 and this enables us to
* be able to interface the external buttons to enable the state transitions. 
*/
// This is the main header file used to initialize Port L so that it can be declared in this file.
#include "button.h"
// Declares port L so that it can be accesed as an input
void extern_switch_init(void)
{
    volatile unsigned short delay = 0;
    RCGCGPIO |= 0x800;         // Enable Port L Gating Clock (bit 11)
    delay++;
    delay++;
    GPIOAMSEL_L &= ~0x3;       // Disable PL0 and PL1 analog function
    GPIOAFSEL_L &= ~0x3;       // Select PL0 and PL1 regular port function
    GPIODIR_L   &= ~0x3;       // Set PL0 and PL1 to input direction
    GPIODEN_L   |=  0x3;       // Enable PL0 and PL1 digital function
}
// This function is called in main files to declare PL0 or PL1 to find the power and person inputs respectively.
unsigned long switch_input(unsigned int pin)
{
    return (GPIODATA_L & (1 << pin)) ? 1 : 0;  // Return 1 if pin is high
}
