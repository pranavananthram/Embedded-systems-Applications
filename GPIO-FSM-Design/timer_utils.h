/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the main timer header file used to appropriately increment the hardware timers and reset as required every second/ operation.
* 
*/
#ifndef TIMER_UTILS_H
#define TIMER_UTILS_H

#include <stdint.h>

// === TM4C Timer-0 Register Definitions ===
// Run-mode Clock Gating Control (Timer)
#define RCGCTIMER   (*((volatile uint32_t *)0x400FE604))

// Base address for GPTM Timer 0
#define TIMER0_BASE 0x40030000

// Timer A registers for Timer 0
#define GPTMCTL0    (*((volatile uint32_t *)(TIMER0_BASE + 0x00C)))
#define GPTMCFG0    (*((volatile uint32_t *)(TIMER0_BASE + 0x000)))
#define GPTMTAMR0   (*((volatile uint32_t *)(TIMER0_BASE + 0x004)))
#define GPTMTAILR0  (*((volatile uint32_t *)(TIMER0_BASE + 0x028)))
#define GPTMRIS0    (*((volatile uint32_t *)(TIMER0_BASE + 0x01C)))
#define GPTMICR0    (*((volatile uint32_t *)(TIMER0_BASE + 0x024)))

// Bit definitions
#define TAEN        0x1       // Timer A Enable
#define TATOI       0x1       // Timer A Time-Out Interrupt (raw)
#define TAMR_PERIODIC 0x2     // GPTMTAMR: periodic mode
#define TAMR_COUNT_DOWN 0x10  // GPTMTAMR: count-down (clear for up-counting)
#define CFG_32BIT   0x0       // GPTMCFG: 32-bit timer


// Call once at startup to power up & configure Timer 0 for 32-bit periodic down-count
void timer0_init(void);

// Busy-wait 'seconds' seconds (uses 16 MHz clock ? seconds·16 000 000 ticks)
void timer0_wait_seconds(uint32_t seconds);

// Busy-wait 'ms' milliseconds (ms·16 000 ticks)
void timer0_wait_ms(uint32_t ms);

// Returns 1 if the PL-pin (0 or 1) reads high continuously for 'ms' ms,
// otherwise returns 0 immediately if it ever goes low.
uint8_t button_held(uint8_t pin, uint32_t ms);

#endif // TIMER_UTILS_H

