#ifndef __TIMER_H__
#define __TIMER_H__
#include <stdint.h>

// Base address for Timer 0
#define TIMER0_BASE 0x40030000

// Timer 0 register macros
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL(n)   (*((volatile uint32_t *)(TIMER0_BASE + 0x00C)))
#define GPTMCFG(n)   (*((volatile uint32_t *)(TIMER0_BASE + 0x000)))
#define GPTMTAMR(n)  (*((volatile uint32_t *)(TIMER0_BASE + 0x004)))
#define GPTMTAILR(n) (*((volatile uint32_t *)(TIMER0_BASE + 0x028)))
#define GPTMRIS(n)   (*((volatile uint32_t *)(TIMER0_BASE + 0x01C)))
#define GPTMICR(n)   (*((volatile uint32_t *)(TIMER0_BASE + 0x024)))
#define GPTMIMR(n)   (*((volatile uint32_t *)(TIMER0_BASE + 0x018)))

// Timer configuration values
#define GPTMCFG_32BIT 0x0        // 32-bit timer configuration
#define TXMR_PERIODIC 0x2        // Periodic timer mode
#define TXCDIR 0x10              // Direction (0 = up, 1 = down)
#define TAEN 0x1                 // Timer A Enable
#define TATOI 0x1                // Timer A timeout raw interrupt

#endif // __TIMER_H__