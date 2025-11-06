# Embedded Systems Projects — TM4C1294NCPDT

This repository contains a series of embedded systems design projects implemented on the **Texas Instruments TM4C1294NCPDT (Tiva C Series LaunchPad)**.  
Each project explores a different aspect of microcontroller-based system design, including **ADC integration**, **timer-based interrupts**, **UART communication**, and **temperature sensing**.  

---

## **Project 1 — ADC and LED Resistance Display**

### **Overview**
This project uses the **ADC module** of the TM4C1294NCPDT to measure the resistance of a potentiometer and display the resistance range using onboard LEDs.  
A **Timer0A** interrupt periodically triggers ADC conversions, and an **ISR (`ADC0SS3_Handler`)** captures the 12-bit ADC values.

### **Implementation Details**
- **System Clock:** 60 MHz  
- **Modules Used:** ADC0, Timer0A, GPIO (Ports N & F)  
- **Functionality:**
  - Reads potentiometer values via ADC.
  - Converts ADC output to resistance (0–10 kΩ).
  - Lights up LEDs sequentially based on resistance range.

| LED Pattern | Resistance Range (kΩ) |
|--------------|------------------------|
| D1           | 0 – 2.5               |
| D1 & D2      | 2.5 – 5.0             |
| D1–D3        | 5.0 – 7.5             |
| D1–D4        | 7.5 – 10.0            |

### **Result**
LEDs illuminated in sequence as the potentiometer resistance increased, confirming correct ADC conversion, timer triggering, and GPIO control.

---

## **Project 2 — Onboard Temperature Measurement and UART Output**

### **Overview**
This project measures the temperature of the TM4C board using the internal temperature sensor and displays it both on the terminal and via UART.  
The system dynamically adjusts the **system clock frequency** to demonstrate temperature variation effects.

### **Implementation Details**
- **System Clock:** 12 MHz, 60 MHz, or 120 MHz (switchable)
- **Modules Used:** ADC0, Timer0A, GPIO (Port J), UART0  
- **Functions:**
  - Reads temperature from ADC input.
  - Converts and prints the temperature to terminal (via UART).
  - Adjusts clock frequency with **PJ0 (SW1)** and **PJ1 (SW2)** buttons.
  - Observes ±2°C variation when switching between clock speeds.

### **Result**
Temperature readings were successfully displayed via both the terminal and PuTTY interface.  
Changing clock speeds produced corresponding temperature changes, validating proper timer and UART operation.

---
### Project 3: LCD Display and Touchscreen Interface — TM4C Microcontroller

This project focused on developing an interactive LCD-based interface on the **TM4C1294NCPDT** microcontroller.  
It was divided into three key stages:

1. **Floating-Point Display:**  
   Modified the `LCD_PrintFloat()` function using `sprintf()` to display floating-point values with two decimal precision. Implemented color control to dynamically update the LCD background.

2. **Temperature Display:**  
   Integrated the on-board ADC to measure the MCU’s internal temperature and displayed it in both **Celsius** and **Fahrenheit**. Added button-based PLL control (PJ0/PJ1) to switch the system clock between **12 MHz** and **120 MHz**, updating the display in real time.

3. **Touchscreen Virtual Buttons:**  
   Implemented virtual buttons on the resistive touchscreen to replace the onboard buttons. Touch inputs within defined coordinate ranges dynamically controlled the PLL frequency while providing visual feedback on the LCD.

**Results:**

- Accurate floating-point and temperature display on the LCD.  
- Dynamic system clock switching with real-time feedback.  
- Interactive touchscreen interface for hardware control.

## **Project 4 — UART Echo Communication**

### **Overview**
This project demonstrates UART-based serial communication by implementing a **real-time echo system**.  
Characters received through UART3 are immediately transmitted back to the sender.

### **Implementation Details**
- **System Clock:** 60 MHz  
- **Modules Used:** UART3, GPIO (Port A)  
- **Functions:**
  - Configures UART3 via `UART3_Init()`.
  - Uses **PA4** (RX) and **PA5** (TX) pins for UART communication.
  - Reads characters from terminal and echoes them back in real time.
  - Sets UART3 to **8-bit, no parity, 1 stop bit** mode.

### **Result**
The system successfully echoed every character sent from the terminal, confirming functional UART3 configuration and reliable full-duplex communication.

---

## **Hardware & Tools**

| Category | Details |
|-----------|----------|
| **Microcontroller** | TI TM4C1294NCPDT (Tiva C Series LaunchPad) |
| **Development Environment** |IAR Embedded Workbench/ Keil µVision / Code Composer Studio (CCS) |
| **Libraries** | TivaWare Peripheral Driver Library |
| **Communication Tools** | PuTTY (Serial Terminal) |
| **Interfaces Used** | ADC0, Timer0A, UART0, UART3, GPIO Ports A, F, J, N, LCD (SSD2119), Resistive Touchscreen |
| **System Clock Range** | 12 MHz – 120 MHz (PLL controlled) |
| **Peripherals** | Potentiometer, LEDs, Onboard Temperature Sensor, 320x240 TFT LCD (SSD2119), Resistive Touchscreen |

---

## **Key Concepts Demonstrated**
- Analog-to-Digital Conversion (ADC)  
- Timer-triggered sampling and interrupt handling  
- GPIO configuration and LED control  
- UART initialization and serial communication  
- LCD SSD2119 display control (drawing, color management, text output)  
- Touchscreen input handling for virtual buttons and interactive control 
- Floating-point data formatting and display  
- Clock frequency scaling with PLL  
- Real-time hardware feedback and user interaction  

---

## **Author**
**Pranav Ananthram**  
*University of Washington — Embedded Systems Design*  
