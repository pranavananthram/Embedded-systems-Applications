# Embedded Systems Lab — Timer and Interrupt Implementation

This project demonstrates the use of **hardware timers** and **interrupts** on the TM4C1294NCPDT microcontroller to drive LEDs and implement a timed traffic light controller.  
The work is divided into two major tasks: implementing timer-based control and interrupt-driven control.

---

## Task 1: Timer-Based Implementation

### Part A: LED Strobing Using Hardware Timers

#### Objective
Use a **general-purpose hardware timer** to toggle the on-board LEDs at a 1 Hz rate, such that each LED lights up in sequence.

#### Procedure
- **Timer Used:** Timer 0A  
- **Mode:** 32-bit periodic, count-up  
- **Clock:** 16 MHz  
- **Reload Value:** 16,000,000 → corresponds to a 1 second delay  

The program configures Timer 0A to generate precise 1-second intervals without busy-wait loops.  
Within the main loop, the `strobe()` function sequentially activates the LEDs on pins **PF0**, **PF4**, **PN0**, and **PN1**, turning one LED on as the previous turns off.

#### Results
The LEDs successfully strobe at a rate of 1 Hz.  
Each LED lights for exactly one second, verified through the 16 MHz clock and hardware timer accuracy.  
The timer reset ensures consistent and drift-free toggling with no irregular delays.

---

### Part B: Interrupt-Driven LED Control Using GPIO Switches

#### Objective
The goal of this task is to control the LED strobing behavior using **GPIO switches** with **interrupt-driven logic**.

#### Procedure
- **Input pins:** PJ0 and PJ1  
- **Output pins:** PN0 and PN1  

The behavior is implemented as follows:
1. LED **PN0** strobes at a rate of **1 Hz** using the Timer 0A interrupt.  
2. When the user presses **PJ0** (triggering a GPIO interrupt), LED PN0 stops strobing and switches off. At this point, **PN1** turns on and remains lit.  
3. When the user presses **PJ1**, LED PN1 switches off, the timer resets, and **PN0** resumes strobing at 1 Hz.  

This setup uses the same interrupt mechanism as in Part A, but adds **external input interrupts** to dynamically change LED behavior.

#### Results
This implementation successfully enables real-time LED control using GPIO inputs.  
The LEDs respond instantly to button presses while the interrupt system maintains efficient, non-blocking background operation.  
The result is a clean, hardware-driven LED control system that demonstrates the integration of **timers**, **interrupts**, and **GPIO event handling**.

### Part C: Interrupt-Based Timed Traffic Light Controller

#### Objective
The objective of this procedure is to recreate the timed traffic controller from Task 1 Part B using **interrupts** for timekeeping instead of blocking delays, resulting in an efficient, event-driven implementation.

#### Procedure
- **Timer 0A Configuration:**
  - Mode: 32-bit periodic, count-down  
  - Load value: 16,000 → produces **1 ms** intervals at a 16 MHz system clock  
  - Interrupt enabled every 1 ms (handled by `Timer0A_Handler`)  

- **Interrupt Handler (`Timer0A_Handler`):**
  - Increments a global `system_time_ms` counter on every interrupt.  
  - Tracks 5-second intervals using a local counter.  
  - Sets a `timer_expired` flag whenever 5 seconds elapse.

- **Utility Functions:**
  - `timer0_wait_ms()` and `timer0_wait_seconds()` — provide **non-blocking delays** based on `system_time_ms`.  
  - `button_held()` — determines whether a button is pressed continuously for 2 seconds using the same timing reference.

This approach allows the traffic light FSM to maintain accurate timing for both **5-second state transitions** and **2-second button-press detection**, all handled via interrupts rather than delay loops.

#### Results
The interrupt-driven traffic light controller accurately replicates the behavior of the timer-based version.  
It performs seamless **5-second state transitions**, correctly detects **2-second button holds**, and operates entirely **non-blockingly**.  
This design showcases an efficient use of interrupts for real-time system control while maintaining precise timing and responsiveness.

