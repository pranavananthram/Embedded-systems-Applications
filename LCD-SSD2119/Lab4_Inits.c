#include "PLL_Header.h"
#include "Lab4_Inits.h"

// STEP 0a: Include your header file here
#include "registers.h"
#include <stdint.h>

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void LED_Init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x20; // enable port F
  RCGCGPIO |= 0x1000; // enable port N
  delay++; delay++; // wait for effect

  GPIODIR_F |= 0x1; // set PF0 output
  GPIODIR_F |= 0x10; // set PF4 output
  GPIODIR_N |= 0x1; // set PN0 output
  GPIODIR_N |= 0x2; // set PN1 output

  GPIODEN_F |= 0x1; // enable PF0 digital
  GPIODEN_F |= 0x10; // enable PF4 digital
  GPIODEN_N |= 0x1; // enable PN0 digital
  GPIODEN_N |= 0x2; // enable PN1 digital
}

void SW_Init(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x100; // enable port J
  delay++; delay++; // wait for effect
  
  // PJ0, PJ1 input by default
  
  GPIODEN_J |= 0x1; // enable PJ0 digital
  GPIODEN_J |= 0x2; // enable PJ1 digital
    
  GPIOPUR_J |= 0x1; // enable PJ0 internal pull-up
  GPIOPUR_J |= 0x2; // enable PJ0 internal pull-up
  
  GPIOIM_J |= 0x3; // capture interrupts from pins 0,1
  EN1 |= 0x1 << 19; // enable interrupt 51 (GPIO port J)
}

// READ INTERNAL TEMP SENSOR FOR 1B
void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x1;
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  volatile unsigned short delay = 0;
  delay++; delay++;
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC &= ~((uint32_t) 0xF); // clear lower 4 bits (CS)
  ADCCC |= 0x1;
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  RCGCGPIO |= 1<<4; // enable port E
  // 2.7: Delay for RCGCGPIO
  volatile unsigned short delay2 = 0;
  delay2++; delay2++;
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= 0x8; // set PE3 bit
  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~((uint32_t) 0xF); // clear PE3 bit
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= 0xF; // enable analog functions for PE3
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS &= ~((uint32_t) 0xF);
  // 2.12: Select timer as the trigger for SS3
  ADCEMUX &= ~((uint32_t) 0xF000); // clear EM3 bits
  ADCEMUX |= 0x5000; // timer is trigger
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSMUX3 &= ~((uint32_t) 0xF); // select AIN0 (assumes EMUX0 bit in ACDSSEMUX3 is cleared)
  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3 |= 0xC; // TEMP SENSOR is read, one conversion per sample, raw interrupt, end of conversion bit,
  ADCSSTSH3 |= 0x4; // sample and hold width at least 16 clocks (see datasheet)
  
  // disable diffential sample (single-ended sampling, see 15.3.5)
  // 2.15: Set the SS3 interrupt mask
  ADCIM |= 0x8;
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  EN0 |= 0x1 << 17;
  // 2.17: Enable ADC0 SS3
  ADCACTSS |= 0x8;
}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x01; // enable GPTM 0
  delay++; delay++; // wait for effect

  GPTMCTL_0 &= ~((uint32_t) 0x101); // disable GPTM 0 A/B

  GPTMCFG_0 = 0x00000000; // per spec.
  GPTMCFG_0 &= ~((uint32_t) 0x7); // select 32-bit config.
   
  GPTMTAMR_0 &= ~((uint32_t) 0x3); // clear lower 2 (TAMR) bits
  GPTMTAMR_0 |= 0x2; // enable periodic timer mode

  GPTMTAMR_0 &= ~((uint32_t) 0x10); // set timer to count down
  GPTMTAILR_0 = 16000000; // set 1 Hz blink rate
  
  GPTMCTL_0 |= 0x1 << 5; // enable ADC trigger (TAOTE bit)
  GPTMADCEV_0 |= 0x1; // enable ADC trigger on 0A time-out (TATOADCEN bit)
  
  GPTMCTL_0 |= 0x101; // enable GPTM 0 A/B
  
  GPTMIMR_0 |= 0x01; // enable timer A time-out interrupt
}