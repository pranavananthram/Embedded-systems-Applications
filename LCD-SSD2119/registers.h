/*
* Rishi Roy
* 2427731
* 05/14/2025
* Registers used to setup GPIOs, GPTMs, Interrupts, and ADCs.
*/

#ifndef _REGISTERS_H_
#define _REGISTERS_H_

/* # GIPO REGISTERS */
// GPIO clock gating
#define RCGCGPIO *((volatile uint32_t *) 0x400FE608)
// GPIO port F
#define GPIODIR_F   *((volatile uint32_t *)0x4005D400)
#define GPIODEN_F   *((volatile uint32_t *)0x4005D51C)
#define GPIODATA_F  *((volatile uint32_t *)0x4005D3FC)
// GPIO port N
#define GPIODIR_N   *((volatile uint32_t *) 0x40064400)
#define GPIODEN_N   *((volatile uint32_t *) 0x4006451C)
#define GPIODATA_N  *((volatile uint32_t *) 0x400643FC)
// GPIO port E
#define GPIOAFSEL_E *((volatile uint32_t *) 0x4005C420)
#define GPIODEN_E   *((volatile uint32_t *) 0x4005C51C)
#define GPIOAMSEL_E *((volatile uint32_t *) 0x4005C528)
// GPIO port J
#define GPIODEN_J *((volatile uint32_t *) 0x4006051C)
#define GPIODATA_J *((volatile uint32_t *) 0x400603FC)
#define GPIOPUR_J *((volatile uint32_t *) 0x40060510)


/* # TIMER REGISTERS */
// GPTM clock gating
#define RCGCTIMER   *((volatile uint32_t *) 0x400FE604)
// GPTM 0
#define GPTMCTL_0   *((volatile uint32_t *) 0x4003000C)
#define GPTMCFG_0   *((volatile uint32_t *) 0x40030000)
#define GPTMTAMR_0  *((volatile uint32_t *) 0x40030004)
#define GPTMTAILR_0 *((volatile uint32_t *) 0x40030028)
#define GPTMRIS_0   *((volatile uint32_t *) 0x4003001C)
#define GPTMICR_0   *((volatile uint32_t *) 0x40030024)
#define GPTMIMR_0   *((volatile uint32_t *) 0x40030018)
#define GPTMADCEV_0 *((volatile uint32_t *) 0x40030070)


/* # INTERRUPT REGISTERS */
#define EN0     *((volatile uint32_t *) 0xE000E100)
#define EN1     *((volatile uint32_t *) 0xE000E104)
// port J
#define GPIOIM_J  *((volatile uint32_t *) 0x40060410)
#define GPIOIS_J  // defaults to detecting edges
#define GPIOIEV_J // defaults to detecting falling edges (or low levels)
#define GPIOICR_J *((volatile uint32_t *) 0x4006041C)
#define GPIORIS_J *((volatile uint32_t *) 0x40060414)


/* # ADC REGISTERS */
#define RCGCADC     *((volatile uint32_t *) 0x400FE638)
#define ADCCC       *((volatile uint32_t *) 0x40038FC8)
#define ADCACTSS    *((volatile uint32_t *) 0x40038000)
#define ADCEMUX     *((volatile uint32_t *) 0x40038014)
#define ADCSSMUX3   *((volatile uint32_t *) 0x400380A0)
#define ADCSSCTL3   *((volatile uint32_t *) 0x400380A4)
#define ADCIM       *((volatile uint32_t *) 0x40038008)
#define ADCISC      *((volatile uint32_t *) 0x4003800C)
#define ADCSSFIFO3  *((volatile uint32_t *) 0x400380A8)
#define ADCSSTSH3   *((volatile uint32_t *) 0x4003805C)

#endif
