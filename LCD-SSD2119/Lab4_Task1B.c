#include "Lab4_Inits.h"
#include "PLL_Header.h"
#include "registers.h"
#include <stdint.h>
#include <stdbool.h>
#include "tm4c1294ncpdt.h"
#include "SSD2119_Touch.h"
#include "SSD2119_Display.h"
#include <stddef.h> 

uint32_t ADC_value;

void LCD_PrintFloat(double num); // Assuming this is already defined

int main(void) { 
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);
  LCD_Init();
  LCD_PrintFloat(5);
  ADCReadPot_Init();
  TimerADCTriger_Init();
  SW_Init();

  while (1) {
    float temp_C = -75 * (ADC_value / 4095.0 * 3.3) + 147.5;
    float temp_F = temp_C * 9.0 / 5.0 + 32.0;

    LCD_PrintString("The current temperature is ");
    LCD_PrintFloat(temp_C);
    LCD_PrintString(" C, ");
    LCD_PrintFloat(temp_F);
    LCD_PrintString(" F.\n");

    LCD_PrintString("The current clock frequency is ");
    LCD_PrintFloat((double)freq);  // cast enum to double
    LCD_PrintString(" MHz.\n");
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