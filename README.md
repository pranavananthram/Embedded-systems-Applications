# ⚙️ Embedded Systems Projects — TM4C1294NCPDT

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

## **Project 3 — UART Echo Communication**

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
| **Development Environment** | Keil µVision / Code Composer Studio (CCS) |
| **Libraries** | TivaWare Peripheral Driver Library |
| **Communication Tools** | PuTTY (Serial Terminal) |
| **Interfaces Used** | ADC0, Timer0A, UART0, UART3, GPIO Ports A, F, J, N |
| **System Clock Range** | 12 MHz – 120 MHz (PLL controlled) |
| **Peripherals** | Potentiometer, LEDs, Onboard Temperature Sensor |

---

## **Key Concepts Demonstrated**
- Analog-to-Digital Conversion (ADC)  
- Timer-triggered sampling and interrupt handling  
- GPIO configuration and LED control  
- UART initialization and serial communication  
- Clock frequency scaling with PLL  
- Temperature sensing and real-time data output  

---

## **Author**
**Pranav Ananthram**  
*University of Washington — Embedded Systems Design*  
