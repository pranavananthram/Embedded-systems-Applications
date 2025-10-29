/*
* Pranav Ananthram
* 2122059
* 5/16/2025
*This is the main file for Lab 3 task 1B and is used to initialize all the necessary modules to measure the temperature of the board
* based on the current clock frequency by sampling the ADC value
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

#include "Lab3b_Inits.h"
#include "lab3-1b.h"
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

uint32_t ADC_value;
int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  //LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float temperature;
  while (1) {
    temperature = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    printf("%f\n", temperature);
  }
  return 0;
}

void ADC0SS3_Handler(void) {
   ADCISC_0 |= SS3_INTERRUPT_CLEAR; // clear the interrupt flag
   ADC_value = ADCSSFIFO3_0 & 0xFFF; // save adc value to global variable
}

void GPIOPortJ_Handler(void) {
  GPIOICR_J |= 0x03; // Clear interrupt flags for PJ0 and PJ1
  enum frequency freq = PRESET2; // Default frequency
  
  if ((GPIODATA_J & 0x01) == 0) { // SW1 (PJ0) pressed (active low)
    freq = PRESET3; // 12 MHz
    printf("SW1 pressed, switching to 12 MHz\n");
  } else if ((GPIODATA_J & 0x02) == 0) { // SW2 (PJ1) pressed (active low)
    freq = PRESET1; // 120 MHz
   printf("SW2 pressed, switching to 120 MHz\n");
  }
  
  PLL_Init(freq);
}
