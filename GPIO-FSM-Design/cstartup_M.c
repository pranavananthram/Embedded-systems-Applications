/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the file used to declare the appropriate vector tables for part A of task 2
* 
*/
/**************************************************
 *
 * This file contains an interrupt vector for Cortex-M written in C.
 * The actual interrupt functions must be provided by the application developer.
 *
 * Modified to include Timer0A_Handler for IRQ 19 (Vector 35).
 *
 **************************************************/

#pragma language=extended
#pragma segment="CSTACK"

extern void __iar_program_start(void);

extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);
extern void Timer0A_Handler(void);  // <-- Added prototype

typedef void (*intfunc)(void);
typedef union { intfunc __fun; void *__ptr; } intvec_elem;

#pragma location = ".intvec"
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe("CSTACK") },
  __iar_program_start,

  NMI_Handler,           // 2
  HardFault_Handler,     // 3
  MemManage_Handler,     // 4
  BusFault_Handler,      // 5
  UsageFault_Handler,    // 6
  0,                     // 7
  0,                     // 8
  0,                     // 9
  0,                     // 10
  SVC_Handler,           // 11
  DebugMon_Handler,      // 12
  0,                     // 13
  PendSV_Handler,        // 14
  SysTick_Handler,       // 15

  // External IRQs begin here (Index 16 onward)
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 16 25
  0, 0, 0, 0, 0, 0, 0, 0, 0,     // 26 34
  Timer0A_Handler,  // 19: Timer 0A (IRQ 19, Vector 35)

  // Fill unused vectors up to desired vector count if needed
};

#pragma call_graph_root = "interrupt"
__weak void NMI_Handler(void) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void HardFault_Handler(void) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void MemManage_Handler(void) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void BusFault_Handler(void) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void UsageFault_Handler(void) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void SVC_Handler(void) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void DebugMon_Handler(void) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void PendSV_Handler(void) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void SysTick_Handler(void) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void Timer0A_Handler(void)
{
    while (1) {}  // Replace with your ISR logic in main.c
}

void __cmain(void);
__weak void __iar_init_core(void);
__weak void __iar_init_vfp(void);

#pragma required=__vector_table
void __iar_program_start(void)
{
  __iar_init_core();
  __iar_init_vfp();
  __cmain();
}
