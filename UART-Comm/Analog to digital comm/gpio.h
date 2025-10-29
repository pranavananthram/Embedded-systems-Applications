#ifndef GPIO_H
#define GPIO_H

// Base addresses
#define SYSCTL_BASE           0x400FE000
#define GPIO_PORTF_BASE       0x4005D000
#define GPIO_PORTN_BASE       0x40064000
#define GPIO_PORTE_BASE       0x4005C000
#define TIMER0_BASE           0x40030000
#define ADC0_BASE             0x40038000
#define NVIC_BASE             0xE000E000

// SYSCTL registers
#define SYSCTL_RCGCGPIO_R     (*((volatile unsigned long *)(SYSCTL_BASE + 0x608)))
#define SYSCTL_RCGCADC_R      (*((volatile unsigned long *)(SYSCTL_BASE + 0x638)))
#define SYSCTL_RCGCTIMER_R    (*((volatile unsigned long *)(SYSCTL_BASE + 0x604)))
#define SYSCTL_PRTIMER_R      (*((volatile unsigned long *)(SYSCTL_BASE + 0xA04)))
#define SYSCTL_PRGPIO_R       (*((volatile unsigned long *)(SYSCTL_BASE + 0xA08)))
#define SYSCTL_PLLFREQ0_R     (*((volatile unsigned long *)(SYSCTL_BASE + 0x160)))
#define SYSCTL_PLLSTAT_R      (*((volatile unsigned long *)(SYSCTL_BASE + 0x168)))
#define SYSCTL_ALTCLKCFG_R    (*((volatile unsigned long *)(SYSCTL_BASE + 0x138)))

// NVIC
#define NVIC_EN0_R            (*((volatile unsigned long *)(NVIC_BASE + 0x100)))

// GPIO PORT F
#define GPIO_PORTF_DIR_R      (*((volatile unsigned long *)(GPIO_PORTF_BASE + 0x400)))
#define GPIO_PORTF_DEN_R      (*((volatile unsigned long *)(GPIO_PORTF_BASE + 0x51C)))

// GPIO PORT N
#define GPIO_PORTN_DIR_R      (*((volatile unsigned long *)(GPIO_PORTN_BASE + 0x400)))
#define GPIO_PORTN_DEN_R      (*((volatile unsigned long *)(GPIO_PORTN_BASE + 0x51C)))

// GPIO PORT E
#define GPIO_PORTE_AFSEL_R    (*((volatile unsigned long *)(GPIO_PORTE_BASE + 0x420)))
#define GPIO_PORTE_DEN_R      (*((volatile unsigned long *)(GPIO_PORTE_BASE + 0x51C)))
#define GPIO_PORTE_AMSEL_R    (*((volatile unsigned long *)(GPIO_PORTE_BASE + 0x528)))
#define GPIO_PORTE_DIR_R      (*((volatile unsigned long *)(GPIO_PORTE_BASE + 0x400)))

// Timer 0
#define TIMER0_CTL_R          (*((volatile unsigned long *)(TIMER0_BASE + 0x00C)))
#define TIMER0_CFG_R          (*((volatile unsigned long *)(TIMER0_BASE + 0x000)))
#define TIMER0_TAMR_R         (*((volatile unsigned long *)(TIMER0_BASE + 0x004)))
#define TIMER0_TAILR_R        (*((volatile unsigned long *)(TIMER0_BASE + 0x028)))
#define TIMER0_ICR_R          (*((volatile unsigned long *)(TIMER0_BASE + 0x024)))
#define TIMER0_ADCCTL_R       (*((volatile unsigned long *)(TIMER0_BASE + 0x070)))

// ADC0
#define ADC0_ACTSS_R          (*((volatile unsigned long *)(ADC0_BASE + 0x000)))
#define ADC0_EMUX_R           (*((volatile unsigned long *)(ADC0_BASE + 0x014)))
#define ADC0_SSMUX3_R         (*((volatile unsigned long *)(ADC0_BASE + 0x0A0)))
#define ADC0_SSCTL3_R         (*((volatile unsigned long *)(ADC0_BASE + 0x0A4)))
#define ADC0_IM_R             (*((volatile unsigned long *)(ADC0_BASE + 0x008)))
#define ADC0_CC_R             (*((volatile unsigned long *)(ADC0_BASE + 0xFC8)))

// Bit masks for SYSCTL
#define SYSCTL_RCGCGPIO_R4    0x00000010 // Port E
#define SYSCTL_RCGCGPIO_R5    0x00000020 // Port F
#define SYSCTL_RCGCGPIO_R12   0x00001000 // Port N
#define SYSCTL_RCGCADC_R0     0x00000001
#define SYSCTL_RCGCTIMER_R0   0x00000001
#define SYSCTL_PRTIMER_R0     0x00000001

// GPIO Pins
#define GPIO_PIN_0            0x01
#define GPIO_PIN_1            0x02
#define GPIO_PIN_4            0x10

// ADC Configuration
#define ADC_ACTSS_ASEN3           0x00000008
#define ADC_SSCTL3_END0           0x00000002
#define ADC_SSCTL3_IE0            0x00000004
#define ADC_IM_MASK3              0x00000008
#define NVIC_EN0_INT14            0x00004000 // ADC0 SS3 Interrupt

// ADC Trigger Event Select (for EMUX register)
#define ADC_EMUX_EM3_M            (0xF << 12)   // Sample Sequencer 3 trigger source mask
#define ADC_EMUX_EM3_TIMER        (0x5 << 12)   // Timer trigger for SS3

// Timer Configuration
#define TIMER_CFG_32_BIT_TIMER    0x0           // 32-bit timer configuration

// Timer A Mode
#define TIMER_TAMR_TAMR_PERIOD    0x2           // Periodic Timer mode
#define TIMER_TAMR_TACDIR         (1 << 4)      // Timer counts up

// Timer Control
#define TIMER_CTL_TAEN            0x00000001

// Timer ADC Event Select
#define TIMER_ADCCTL_TAOTE        (1 << 0)      // Timer A Output Trigger Enable
#define TIMER_ADCCTL_TAEVENT      0x0000000C    // ADC event mask
#define TIMER_ADCCTL_TAEVENT_POS  (0x0 << 1)    // Positive edge trigger

// Timer Interrupts
#define TIMER_ICR_TATOCINT        0x00000001


#endif // GPIO_H
