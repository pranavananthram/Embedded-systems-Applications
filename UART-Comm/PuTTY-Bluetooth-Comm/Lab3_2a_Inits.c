/*
* Pranav Ananthram
* 2122059
* 5/16/2025
*This file is used to initialize all the necessary modules to read the temperature values, set and switch the frequency based on input
* and initialize the UART module to transmit data through PUTTY. 
*/
/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab3_2a_Inits.h"
#include "lab3-2a.h"
// STEP 0a: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

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



void swith_init(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO |= RCGCGPIO_J_EN;  // Enable GPIO Port J
  delay++;
  delay++;                    // Delay for clock stabilization

  GPIODIR_J = 0x00;           // Set PJ0 and PJ1 as input
  GPIODEN_J = 0x03;           // Enable digital function on PJ0 and PJ1 (0x01 | 0x02)
  GPIOPUR_J = 0x03;           // Enable pull-up resistors on PJ0 and PJ1

  EN1 |= PORTJ_INTERRUPT_EN; // Enable Port J interrupt in NVIC
  GPIOIM_J = 0x00;            // Mask all interrupts temporarily
  GPIOIS_J &= ~0x03;          // Edge-sensitive for PJ0 and PJ1
  GPIOIBE_J &= ~0x03;         // Disable both-edge triggering
  GPIOIEV_J &= ~0x03;         // Falling edge trigger
  GPIOICR_J |= 0x03;          // Clear any prior interrupts on PJ0 and PJ1
  GPIOIM_J |= 0x03;           // Unmask interrupts on PJ0 and PJ1
}


void ADCReadPot_Init(void) {
 // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= RCGCADC_0_EN;
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  delay++;
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC_0 = ADCCC_ALTCLKCFG;
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
   RCGCGPIO |= RCGCGPIO_E_EN;
  // 2.7: Delay for RCGCGPIO
  delay++;
  delay++;
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= PE0;
  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~PE0;
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= PE0;
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS_0 &= ~ASEN3; 
  // 2.12: Select timer as the trigger for SS3
  ADCEMUX_0 = EM3_TIMER;
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSEMUX3 = 0x0; 
  ADCSSMUX3 = AIN3; 
  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3 = SS3_INTERRUPT_EN;
  // 2.15: Set the SS3 interrupt mask
  ADCIM_0 = SS3_IM;
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  EN0 |= ADCSS3_INTERRUPT_EN;
  // 2.17: Enable ADC0 SS3
  ADCACTSS_0 |= ASEN3;
}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  // YOUR CODE HERE
  RCGCTIMER |= RCGCTIMER_0_EN; // Enable timer 0 clock
  GPTMCTL_0 = 0x0; // Disable timer 0
  GPTMCTL_0 |= TAOTE; // enable output trigger
  GPTMCFG_0 = CFG_32BIT; // Set 32-bit mode and enable output trigger
  GPTMTAMR_0 |= (TAMR_PERIODIC | TAMR_COUNT_DOWN); // Set timer to periodic and countdown
  GPTMTAILR_0 = FREQ_1HZ; // Set frequency to 1Hz
  GPTMADCEV_0 |= TATOADCEN; // enable trigger on timeout event
  GPTMCTL_0 |= 0x1; // Enable timer 0
}
void UART0_Init(void) {
  volatile unsigned short delay = 0;
  RCGCUART |= RCGCUART_0_EN; // enable clock to UART0
  RCGCGPIO |= RCGCGPIO_A_EN; // enable clock to GPIO port A
  delay++;
  delay++;
  delay++; // delay for three clock cycles before further configuration
  GPIOAFSEL_A |= 0x3; // enable alternate function for PA0 and PA1
  GPIODEN_A |= 0x3; // enable digital function for PA0 and PA1
  GPIODR2R_A |= 0x3; // setting PA0 and PA1 to 2mA drive
  GPIOPCTL_A |= 0x11; // enable U0Tx and U0Rx function for PA0 and PA1
  
  UARTCTL_0 &= ~0x1; // disable UART0
  // Baud rate is 9600, SysClk is 16M
  UARTIBRD_0 = 0x68; // decimal 104 in hex for Baud rate
  UARTFBRD_0 = 0xB; // decimal 11 in hex for Baud rate
  UARTLCRH_0 = UARTLCRH_8BIT; // set word length to 8 bit, keep everything else default
  UARTCC_0 = 0x5; // set clock source to alternate clock
  UARTCTL_0 |= 0x1; // enable UART0
}
// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler
