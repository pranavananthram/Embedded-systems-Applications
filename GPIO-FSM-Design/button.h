/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This file is used to initialize ports L so that it can access PL0 and PL1 as input based on the external user switches, and allows other functions to recieve this input from extern_switch_init
*/
// Defines the header
#ifndef BUTTON_H
#define BUTTON_H
//Standard library
#include <stdint.h>
// Defines the clock for GPIO pins and port L so that it can access the data and direction of port L
#define RCGCGPIO      (*((volatile uint32_t *)0x400FE608)) // Internal clock
#define GPIOAMSEL_L   (*((volatile uint32_t *)0x40062528)) // Used to change the data, direction etc of Port L
#define GPIODIR_L     (*((volatile uint32_t *)0x40062400)) // Used to change the data, direction etc of Port L
#define GPIODEN_L     (*((volatile uint32_t *)0x4006251C))// Used to change the data, direction etc of Port L
#define GPIOAFSEL_L   (*((volatile uint32_t *)0x40062420))// Used to change the data, direction etc of Port L
#define GPIODATA_L    (*((volatile uint32_t *)0x400623FC))// Used to change the data, direction etc of Port L
//#define GPIODATA_E    (*((volatile uint32_t *)0x4005C3FC)) 
// Allows other modules to recieve the input from extern_switch_init and switch_input so that it can receive the user Input.
void extern_switch_init(void);
unsigned long switch_input(unsigned int pin);

#endif
