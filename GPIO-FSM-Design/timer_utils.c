/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the main timer file used to appropriately increment the hardware timers and reset as required every second/ operation.
* 
*/
#include "timer_utils.h"
#include "button.h"    // for switch_input()

void timer0_init(void) {
    // 1) enable clock for Timer0
    RCGCTIMER |= (1 << 0);
    // 2) disable Timer A
    GPTMCTL0 &= ~TAEN;
    // 3) 32-bit mode
    GPTMCFG0 = CFG_32BIT;
    // 4–6) periodic, count-down
    GPTMTAMR0 = TAMR_PERIODIC | TAMR_COUNT_DOWN;
}

void timer0_wait_seconds(uint32_t seconds) {
    // reload & start
    GPTMCTL0   &= ~TAEN;
    GPTMTAILR0 = seconds * 16000000U;
    GPTMCTL0   |= TAEN;
    // wait for timeout
    while (!(GPTMRIS0 & TATOI)) { }
    // clear flag & stop
    GPTMICR0 = TATOI;
    GPTMCTL0 &= ~TAEN;
}

void timer0_wait_ms(uint32_t ms) {
    GPTMCTL0   &= ~TAEN;
    GPTMTAILR0 = ms * 16000U;
    GPTMCTL0   |= TAEN;
    while (!(GPTMRIS0 & TATOI)) { }
    GPTMICR0 = TATOI;
    GPTMCTL0 &= ~TAEN;
}

uint8_t button_held(uint8_t pin, uint32_t ms) {
    // if button isn’t even pressed, bail out
    if (!switch_input(pin)) return 0;
    // otherwise wait and verify it stayed pressed
    timer0_wait_ms(ms);
    return switch_input(pin) ? 1 : 0;
}
