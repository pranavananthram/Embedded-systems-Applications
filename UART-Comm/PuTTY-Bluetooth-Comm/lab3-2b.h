/*
* Pranav Ananthram
* 2122059
* 5/16/2025
*This is the main header file for Lab 3 task 2b and is used to initialize all the necessary ports.
*/
#ifndef __LAB3_H__
#define __LAB3_H__

//------------------GPIO Macros----------------------
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define RCGCGPIO_F_EN 0x00000020
#define RCGCGPIO_N_EN 0x00001000
#define RCGCGPIO_E_EN 0x00000010

#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))

#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))

#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))

#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))

#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))

#define GPIOIS_J (*((volatile uint32_t *)0x40060404))
#define GPIOIBE_J (*((volatile uint32_t *)0x40060408))
#define GPIOIEV_J (*((volatile uint32_t *)0x4006040C))
#define GPIOIM_J (*((volatile uint32_t *)0x40060410))
#define GPIORIS_J (*((volatile uint32_t *)0x40060414))
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C))
#define PORTJ_INTERRUPT_EN 0x00080000
#define RCGCGPIO_J_EN 0x00000100
#define EN1 (*((volatile uint32_t *)0xE000E104))
#define PE0 0x01

//------------------ADC Macros----------------------
#define RCGCADC (*((volatile uint32_t *)0x400FE638))
#define RCGCADC_0_EN 0x1

#define ADCCC_0 (*((volatile uint32_t *)0x40038FC8))
#define ADCCC_ALTCLKCFG 0x1

#define ADCACTSS_0 (*((volatile uint32_t *)0x40038000))
#define ASEN3 0x00000008

#define ADCEMUX_0 (*((volatile uint32_t *)0x40038014))
#define EM3_TIMER 0x5000

#define ADCSSEMUX3 (*((volatile uint32_t *)0x400380B8))
#define ADCSSMUX3 (*((volatile uint32_t *)0x400380A0))
#define AIN3 0x3

#define ADCSSCTL3 (*((volatile uint32_t *)0x400380A4))
#define SS3_INTERRUPT_EN 0x4

#define ADCIM_0 (*((volatile uint32_t *)0x40038008))
#define SS3_IM 0x8

#define EN0 (*((volatile uint32_t *)0xE000E100))
#define ADCSS3_INTERRUPT_EN 0x00020000

#define ADCISC_0 (*((volatile uint32_t *)0x4003800C))
#define SS3_INTERRUPT_CLEAR 0x8

#define ADCSSFIFO3_0 (*((volatile uint32_t *)0x400380A8))

//------------------Timer Macros----------------------
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define RCGCTIMER_0_EN 0x01

#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))

#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define CFG_32BIT 0x00
#define TAOTE 0x20

#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define TAMR_PERIODIC 0x0002
#define TAMR_COUNT_DOWN 0x0000

#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define FREQ_1HZ 0xF42400 // 16M in hex

#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

#define GPTMADCEV_0 (*((volatile uint32_t *)0x40030070))
#define TATOADCEN 0x1



#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

#define RCGCGPIO_A_EN 0x00000001

#define GPIOAFSEL_A (*((volatile uint32_t *)0x40058420))
#define GPIODEN_A (*((volatile uint32_t *)0x4005851C))
#define GPIOPCTL_A (*((volatile uint32_t *)0x4005852C))
#define GPIODR2R_A (*((volatile uint32_t *)0x40058500))


//------------------UART Macros----------------------
#define RCGCUART (*((volatile uint32_t *)0x400FE618))
#define RCGCUART_3_EN 0x8

#define UARTCTL_3 (*((volatile uint32_t *)0x4000F030))
#define UARTIBRD_3 (*((volatile uint32_t *)0x4000F024))
#define UARTFBRD_3 (*((volatile uint32_t *)0x4000F028))
#define UARTLCRH_3 (*((volatile uint32_t *)0x4000F02C))
#define UARTLCRH_8BIT 0x60
#define UARTCC_3 (*((volatile uint32_t *)0x4000FFC8))
#define UARTDR_3 (*((volatile uint32_t *)0x4000F000))
#define UARTFR_3 (*((volatile uint32_t *)0x4000F018))



#endif //