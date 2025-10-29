/*
* Pranav Ananthram
* 2122059
* 5/16/2025
*This is the main file for Lab 3 task 1 and is used to initialize all the necessary modules to switch on the onboard LEDs
* based on the calculated resistance opbtained from the ADC value measured across the potentiometer. 
*/
/**
 * EE/CSE 474: Lab3 Task1a main function
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include "Lab3_Inits.h"
#include "lab3.h"
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float resistance;
  while (1) {
    // Convert ADC reading (0–4095) to resistance (0–10 kO)
    resistance = (double)ADC_value / 4095.0 * 10.0;

   if (resistance < 2.5) {
  GPIODATA_N = 0x02; // PN1 on (LED1), PN0 off (LED2)
  GPIODATA_F = 0x00; // PF4 and PF0 off (LED3 and LED4)
} else if (resistance < 5.0) {
  GPIODATA_N = 0x03; // PN1 and PN0 on (LED1 and LED2)
  GPIODATA_F = 0x00; // LED3 and LED4 off
} else if (resistance < 7.5) {
  GPIODATA_N = 0x03; // LED1 and LED2 on
  GPIODATA_F = 0x10; // PF4 on (LED3), PF0 off (LED4)
} else {
  GPIODATA_N = 0x03; // LED1 and LED2 on
  GPIODATA_F = 0x11; // PF4 and PF0 on (LED3 and LED4)
}
  }
  return 0;
}

void ADC0SS3_Handler(void) {
   ADCISC_0 |= SS3_INTERRUPT_CLEAR; // clear the interrupt flag
   ADC_value = ADCSSFIFO3_0 & 0xFFF; // save adc value to global variable
}
