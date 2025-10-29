/*
* Pranav Ananthram
* 2122059
* 4/24/2025
* This is the main header file for task 1. In this file, we are initializing port F, N and J  *****make more changes ******* 
*/
#ifndef __HEADER1_H__
#define __HEADER1_H__
#include <stdint.h>
// To set up and change the data for GPIO for PORT N F J
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_N  (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N  (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400)) 
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C)) 
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510)) 
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#endif //__HEADER1_H__
