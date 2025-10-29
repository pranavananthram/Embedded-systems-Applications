/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This file is used to initialize ports L so that it can access PL2,Pl3 and PL4 as output so that it can be displayed using external LEDs, and allows other functions to output the transition in states and user input.
*/
// Defines the header file
#ifndef LED_H
#define LED_H
// Standard library
#include <stdint.h>

#define RCGCGPIO      (*((volatile uint32_t *)0x400FE608)) // Defines the clock for GPIO pins
// Used to change the data, direction etc, of Port L
#define GPIOAMSEL_L   (*((volatile uint32_t *)0x40062528))
#define GPIODIR_L     (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L     (*((volatile uint32_t *)0x4006251C))
#define GPIOAFSEL_L   (*((volatile uint32_t *)0x40062420))
#define GPIODATA_L    (*((volatile uint32_t *)0x400623FC))

// Initialization of the LED module so that other functions can access it.
void LED_init(void);

// LED control functions so that other modules can input 1 or 0 to control which LED is switched on based on its current state
void red_led(uint8_t state); // Accesses red LED
void yellow_led(uint8_t state); // Accesses yellow LED
void green_led(uint8_t state); // Accesses green LED

#endif
