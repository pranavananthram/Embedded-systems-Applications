#include <stdint.h>
#include <stdbool.h>
#include "tm4c1294ncpdt.h"
#include "SSD2119_Touch.h"
#include "SSD2119_Display.h"
#include <stddef.h>

#include "Lab3_Inits.h"
#include "registers.h"

uint32_t ADC_value;
int PLL_label = 12;

int main(void) {
  LCD_Init();
  Touch_Init();                    // Initialize touch screen
  enum frequency freq = PRESET2;   // Start at 60 MHz
  PLL_Init(freq);                  // Apply initial clock
  ADCReadPot_Init();               // Initialize ADC
  TimerADCTriger_Init();           // ADC trigger via Timer0A
  int currentFreq;

  LCD_ColorFill(Color4[5]);
 
  while (1) {
    // Draw wider frequency buttons
    LCD_DrawFilledRect(20, 200, 100, 40, Color4[9]);   // Left: 12 MHz
    LCD_DrawFilledRect(140, 200, 100, 40, Color4[12]); // Right: 120 MHz

    // Normalize touchscreen coordinates
    int X = (Touch_ReadX() - 700) * 240 / 1400;
    int Y = (Touch_ReadY() - 700) * 320 / 820;

    // ? Corrected Y range: 200 to 240
    if ((X >= 20) && (X <= 120) && (Y >= 200) && (Y <= 240)) {
      freq = PRESET3; // 12 MHz
    } else if ((X >= 20) && (X <= 120) && (Y >= 300) && (Y <= 240)) {
      freq = PRESET1; // 120 MHz
    }

    PLL_Init(freq); // Update system clock

    // Set frequency label
    if (freq == PRESET1) currentFreq = 120;
    else if (freq == PRESET3) currentFreq = 12;
    else currentFreq = 60;

    // Display temperature and clock info
    float temp = -75 * (ADC_value / 4095.0 * 3.3) + 147.5;
    char buffer[100];
    LCD_SetCursor(0, 0);
    sprintf(buffer, "The current temperature is %.2f C, %.2f F\n\n", temp, temp * 1.8 + 32);
    LCD_PrintString(buffer);
    sprintf(buffer, "The clock frequency is %d MHz  ", currentFreq);
    LCD_PrintString(buffer);
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
    PLL_label = 12;
  } else if (GPIORIS_J & 0x2) {
    // PJ1 triggered interrupt
    GPIOICR_J |= 0x2; // clear interrupt on PJ1
    PLL_Init(120);
    PLL_label = 120;
  }
}


