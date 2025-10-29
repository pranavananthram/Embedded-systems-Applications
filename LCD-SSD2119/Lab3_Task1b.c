/*
* Rishi Roy
* 2427731
* 05/14/2025
* Display the board temperate every second in terminal I/O.
* SW1 and SW2 change the PLL frequency to 12 MHz or 120 MHz.
*/

#include <stdint.h>
#include <stdio.h>
#include "Lab3_Inits.h"

// STEP 0b: Include your header file here
#include "registers.h"
#include "lighting.h"

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  SW_Init(); // initialize SW1, SW2 GPIO and interrupts
  float resistance;
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    float temp = -75 * (ADC_value / 4095.0 * 3.3) + 147.5; // TODO: check formula
    printf("T: %.2f\n", temp);
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC |= 0x8; // clear SS3 interrupt
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3 & 0xFFF;
}

void port_J_handler(void) {
  if (GPIORIS_J & 0x1) {
    // PJ0 triggered interrupt
    GPIOICR_J |= 0x1; // clear interrupt on PJ0
    PLL_Init(12);
    onboard_1_on();
  } else if (GPIORIS_J & 0x2) {
    // PJ1 triggered interrupt
    GPIOICR_J |= 0x2; // clear interrupt on PJ1
    PLL_Init(120);
    onboard_2_on();
  }
}
