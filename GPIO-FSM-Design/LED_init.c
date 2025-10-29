/*
* Pranav Ananthram
* 2122059
* 5/2/2025
* This file is used to enable the LEDs for PL2 PL3 and PL4 so that it can be accesed and then includes other functions that allows us to specifically use the red, yellow and green LEDS
*/
// These declare the header files so that it can access the respective files.
#include "led.h" // This header file declares port L so that it can access the respective LEDs 
#include <stdint.h> // Standard library
#include "fsm.h" // This header file allows the trafficController module to call the respective functions in this file.
// Declares port L and sets PL2,PL3, and PL4 as outputs so that it can display the correct LED
void LED_init(void)
{
    volatile unsigned short delay = 0;
    RCGCGPIO |= 0x800;        // Enable clock for Port L (bit 11)
    delay++;
    delay++;
    GPIOAMSEL_L &= ~0x1C;     // Disable analog function on PL2, PL3, PL4 
    GPIODIR_L   |=  0x1C;     // Set PL2, PL3, PL4 as output
    GPIOAFSEL_L &= ~0x1C;     // Set regular GPIO function
    GPIODEN_L   |=  0x1C;     // Enable digital function
}
// This function checks when a digital high or 1 is enabled so that it can switch on the red LED and else it will remain off.
void red_led(uint8_t state) {
    if (state)
        GPIODATA_L |= 0x04;  // PL2
    else
        GPIODATA_L &= ~0x04;
}
// This function checks when a digital high or 1 is enabled so that it can switch on the yellow LED and else it will remain off.
void yellow_led(uint8_t state) {
    if (state)
        GPIODATA_L |= 0x08;  // PL3
    else
        GPIODATA_L &= ~0x08;
}
// This function checks when a digital high or 1 is enabled so that it can switch on the green LED and else it will remain off.
void green_led(uint8_t state) {
    if (state)
        GPIODATA_L |= 0x10;  // PL4
    else
        GPIODATA_L &= ~0x10;
}
