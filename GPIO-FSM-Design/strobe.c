#include <stdint.h>  // For uint32_t definition
#include <stdbool.h>
#include "helpers.h"
#include "gpio.h"
#include "timer.h"

// Function to strobe a specific GPIO pin for 1 second
void strobe(volatile uint32_t *io_addr, uint32_t mask) {
    // Set GPIO pin HIGH
    *io_addr = mask;                   // Set GPIO pin HIGH
    
    // Clear Timer A timeout interrupt
    GPTMICR(0) = TATOI;                // Clear Timer A timeout interrupt
    
    // Enable Timer A
    GPTMCTL(0) |= TAEN;                // Enable Timer A
    
    // Wait until timer times out
    while (!(GPTMRIS(0) & TATOI)) {
        // Wait until timer times out
    }
    
    // Set GPIO pin LOW
    *io_addr = 0x00;                   // Set GPIO pin LOW
}