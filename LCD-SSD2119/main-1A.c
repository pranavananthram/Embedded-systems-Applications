/*
*
* Pranav Ananthram
* 2122059
* 5/30/2025
*This is the main file used for Lab 4 Task 1a and is used to initialize all the necessary modules and change the color and print
* a floating point number
*/
#include <stdint.h>
#include <stdbool.h>
#include "tm4c1294ncpdt.h"
#include "SSD2119_Touch.h"
#include "SSD2119_Display.h"
#include <stddef.h> 


int main(void) {
  
  LCD_Init();    
  
  LCD_ColorFill(Color4[5]);
  LCD_PrintFloat(5.01909);
  while(1) {
    
  }
  return 0;
}

