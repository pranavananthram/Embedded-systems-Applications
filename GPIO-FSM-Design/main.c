/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the main  file used to periodically strobe the LEDs using interrupts and declare all the modules
* 
*/
#include <stdint.h>
#include <stdbool.h>
#include "helpers.h"
#include "gpio.h"
#include "timer.h"
#include <stddef.h> 

// === Global Variables for Strobing State ===
volatile uint32_t *current_pin_addr = NULL;
volatile uint32_t current_pin_mask = 0;
volatile uint8_t strobe_step = 0;

// === Strobe Function: Set Pin High and Start Timer ===
void strobe(volatile uint32_t *io_addr, uint32_t mask) {
    current_pin_addr = io_addr;
    current_pin_mask = mask;

    *current_pin_addr = mask;        // Set pin HIGH

    GPTMICR(0) = TATOI;              // Clear any prior interrupts
    GPTMIMR(0) |= TATOI;             // Enable timeout interrupt
    GPTMCTL(0) |= TAEN;              // Start timer
}

// === Timer0A Interrupt Handler ===
#pragma call_graph_root = "interrupt"
void Timer0A_Handler(void) {
    GPTMICR(0) = TATOI;              // Acknowledge interrupt
    GPTMCTL(0) &= ~TAEN;             // Stop timer
    GPTMIMR(0) &= ~TATOI;            // Disable timeout interrupt

    if (current_pin_addr != NULL) {
        *current_pin_addr = 0x00;    // Set pin LOW
    }

    // Advance to next pin
    strobe_step = (strobe_step + 1) % 4;

    switch (strobe_step) {
        case 0: strobe(&GPIODATA(F, BIT(0)), BIT(0)); break;
        case 1: strobe(&GPIODATA(F, BIT(4)), BIT(4)); break;
        case 2: strobe(&GPIODATA(N, BIT(0)), BIT(0)); break;
        case 3: strobe(&GPIODATA(N, BIT(1)), BIT(1)); break;
    }
}

// === Main Function ===
void main(void) {
    // === Clock Configuration ===
    RCGCGPIO = BIT(5) | BIT(8) | BIT(12);  // Enable GPIO clocks: PJ, PF, PN
    RCGCTIMER = BIT(0);                   // Enable Timer 0

    // === Port J Configuration (inputs with pull-ups) ===
    GPIODIR(J) &= ~(BIT(0) | BIT(1));
    GPIODEN(J) = BIT(0) | BIT(1);
    GPIOPUR(J) = BIT(0) | BIT(1);

    // === Port F Configuration (PF0, PF4 as outputs) ===
#define GPIO_LOCK_KEY 0x4C4F434B
#define GPIOLOCK_F (*((volatile uint32_t *)0x4005D520))
#define GPIOCR_F   (*((volatile uint32_t *)0x4005D524))
    GPIOLOCK_F = GPIO_LOCK_KEY;
    GPIOCR_F |= BIT(0);
    GPIODIR(F) = BIT(0) | BIT(4);
    GPIODEN(F) = BIT(0) | BIT(4);

    // === Port N Configuration (PN0, PN1 as outputs) ===
    GPIODIR(N) = BIT(0) | BIT(1);
    GPIODEN(N) = BIT(0) | BIT(1);

    // === Timer0A Configuration ===
    GPTMCTL(0) &= ~TAEN;
    GPTMCFG(0) = GPTMCFG_32BIT;
    GPTMTAMR(0) = TXMR_PERIODIC;
    GPTMTAMR(0) &= ~TXCDIR;         // Count up
    GPTMTAILR(0) = 16000000;        // 1-second interval at 16 MHz

    // === NVIC: Enable IRQ 19 for Timer0A ===
    *((volatile uint32_t *)0xE000E100) |= (1 << 19);

    // === Start First Strobe ===
    strobe_step = 0;
    strobe(&GPIODATA(F, BIT(0)), BIT(0));

    while (1) {
        // Interrupt-driven, nothing to do here
    }
}


