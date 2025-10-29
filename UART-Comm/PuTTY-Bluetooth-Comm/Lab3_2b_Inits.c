/*
* Pranav Ananthram
* 2122059
* 5/16/2025
*This is the main file used to initialize the PLL and the UART module to transmit data through putty, and contains functions that
* read and write a character transmitted through UART 
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



void UART3_Init(void) {
    volatile unsigned short delay = 0;
    RCGCUART |= (1 << 3);       // Enable UART3 clock
    RCGCGPIO |= (1 << 0);       // Enable Port A clock (PA4/PA5)
    delay++; delay++; delay++;  // Delay for clock to stabilize

    // Configure PA4 and PA5 for UART3 (AFSEL + PCTL)
    GPIOAFSEL_A |= (1 << 4) | (1 << 5);   // Enable alternate function
    GPIODEN_A   |= (1 << 4) | (1 << 5);   // Enable digital function
    GPIOPCTL_A &= ~0x00FF0000;            // Clear PCTL bits for PA4, PA5
    GPIOPCTL_A |= 0x00110000;             // Configure PA4, PA5 for UART3

    UARTCTL_3 &= ~0x01;                   // Disable UART3
    UARTIBRD_3 = 390;
    UARTFBRD_3 = 40;

    UARTLCRH_3 = 0x60;                    // 8-bit, no parity, 1 stop bit
    UARTCC_3 = 0x0; // Use system clock (60 MHz)
    UARTCTL_3 |= 0x301;                   // Enable UART3, TXE, RXE
}
char UART3_ReadChar(void) {
    while (UARTFR_3 & (1 << 4));   // Wait until RXFE is 0 (not empty)
    return UARTDR_3 & 0xFF;
}

void UART3_WriteChar(char c) {
    while (UARTFR_3 & (1 << 5));   // Wait until TXFF is 0 (not full)
    UARTDR_3 = c;
}




// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler
