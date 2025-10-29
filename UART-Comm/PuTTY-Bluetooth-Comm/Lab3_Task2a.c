/*
* Pranav Ananthram
* 2122059
* 5/16/2025
*This is the main file for Lab 3 task 2A and is used to initialize all the necessary modules to transmit the temperature values 
* through UART and to the putty interface 
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

#include "Lab3_2a_Inits.h"
#include "lab3-2a.h"
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

uint32_t ADC_value;
int updateTemp = 0;
int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  //LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  UART0_Init();
  float temperature;
  char output[7];
  while (1) {
    updateTemp = 0;
    temperature = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    temperature = roundf(temperature * 100) / 100;
    sprintf(output, "%f", temperature);
    output[5] = 0x0D; // \r in ASCII
    output[6] = 0x0A; // \n in ASCII
    for (int i = 0; i < 7; i++) {
      UARTDR_0 = output[i];
    }
    while (updateTemp != 1);
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  ADCISC_0 = 0x08;              // Clear SS3 interrupt flag
  ADC_value = ADCSSFIFO3_0 & 0xFFF; // Read ADC value
  updateTemp = 1;               // Signal main loop to update
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
