# Embedded Systems Lab — ADC, UART, and Temperature Measurement (TM4C1294NCPDT)

## **Task 1**

---

### **Section 1.A — ADC-Based Potentiometer Resistance Display**

#### **Procedure**
The objective of this section is to use the **ADC module** of the **TM4C1294NCPDT** microcontroller to measure the resistance of a potentiometer and visually display its range using on-board LEDs.

The system:
- Initializes the **system clock** to **60 MHz**.  
- Configures LEDs on **Ports N and F**.  
- Sets up **ADC0** to read the potentiometer.  
- Uses **Timer0A** to periodically trigger ADC conversions.  

When an ADC conversion completes, the **ADC0 interrupt service routine (`ADC0SS3_Handler`)** captures the 12-bit ADC value and stores it in a global variable `ADC_value`.  
In the main loop, this value is converted to a resistance value (0–10 kΩ scale).  
Depending on the measured resistance, a pattern of LEDs is activated to indicate the resistance range visually.

#### **LED Resistance Mapping**
| LED Pattern | Resistance Range (kΩ) |
|--------------|------------------------|
| D1           | 0 – 2.5               |
| D1 & D2      | 2.5 – 5.0             |
| D1–D3        | 5.0 – 7.5             |
| D1–D4        | 7.5 – 10.0            |

#### **Result 1.A**
The system successfully triggered the onboard LEDs according to the potentiometer resistance.  
As the potentiometer was adjusted, LEDs sequentially illuminated in the expected order — confirming correct ADC readings, timing, and LED mapping.

---

### **Section 1.B — Temperature Sensor Display via Terminal**

#### **Procedure**
The goal of this section is to measure and display the **temperature** of the TM4C board through terminal output.

The system:
- Initializes the **system clock** to **60 MHz**.  
- Configures **ADC0** to read temperature sensor values.  
- Uses **Timer0A** for periodic ADC triggers.  
- Converts the ADC readings to temperature using a mathematical formula.  
- Prints the results to the **terminal output**.

Additionally, **Port J buttons (SW1, SW2)** are used to dynamically adjust the clock frequency:
- **SW1 (PJ0):** Reduces clock speed to **12 MHz**  
- **SW2 (PJ1):** Increases clock speed to **120 MHz**

These changes in frequency cause observable temperature variations of approximately ±2°C.

#### **Result 1.B**
The temperature readings were successfully displayed via Terminal I/O.  
Observed changes of ±2°C upon clock adjustments verified proper operation and responsiveness of the system.

---

## **Task 2**

---

### **Section 2.A — UART Serial Communication for Temperature Output**

#### **Procedure**
The objective of this section is to use **UART serial communication** to print temperature readings to a terminal (e.g., **PuTTY**).

This system builds on **Task 1.B** and includes:
- System clock initialization at **60 MHz**.  
- ADC0 configuration for analog input.  
- **Timer0A** setup for periodic ADC sampling.  
- **UART0** initialization for serial communication.  

In the main loop:
1. The system waits for the `updateTemp` flag (set by the `ADC0SS3_Handler` ISR).  
2. Converts the ADC value into a temperature reading.  
3. Rounds the result to two decimal places.  
4. Sends the formatted string to the UART data register.

Two buttons (PJ0, PJ1) again control clock speed (12 MHz and 120 MHz), affecting the temperature readings accordingly.

#### **Result 2.A**
The UART interface successfully displayed real-time temperature readings on the **PuTTY terminal**.  
After identifying the correct COM port through Device Manager, the system continuously streamed accurate temperature data, confirming full functionality.

---

### **Section 2.B — UART Echo (Return-to-Sender) Functionality**

#### **Procedure**
The goal of this section is to implement a **UART echo system** — receiving a character through UART and immediately transmitting it back.

Steps:
1. Initialize the **system clock** to **60 MHz** using `PLL_Init(PRESET2)`.  
2. Configure **UART3** via `UART3_Init()`.  
3. Set up **GPIO Port A (pins 4 & 5)** for UART operation.  
4. Define UART baud rate using `UARTIBRD_3` and `UARTFBRD_3`.  
5. Set UART3 mode to **8-bit, no parity, 1 stop bit**.  
6. Implement:
   - `UART3_ReadChar()` — waits for and reads incoming characters.  
   - `UART3_WriteChar(char c)` — waits until ready and transmits the character.

The program runs an infinite loop that continuously reads a character from the terminal and echoes it back, forming a simple serial echo interface.

#### **Result 2.B**
The UART echo system functioned as intended.  
Characters sent through the terminal were instantly echoed back, confirming reliable full-duplex UART communication and proper GPIO setup.

---

## **Summary**
Across all tasks:
- **ADC, Timer, GPIO, and UART modules** of the TM4C1294NCPDT were successfully configured and utilized.  
- The experiments demonstrated key embedded concepts — **sensor interfacing**, **data conversion**, **clock frequency scaling**, and **serial communication**.  
- Each subtask produced correct and observable results, validating system design and implementation.

---

### **Hardware & Tools**
- **Microcontroller:** TM4C1294NCPDT (Tiva C Series LaunchPad)  
- **Software:** Keil µVision / CCS, PuTTY, TivaWare  
- **Interfaces Used:** ADC0, UART0, UART3, Timer0A, GPIO (Ports N, F, J, A)  

---

### **Author**
**Pranav Ananthram**  
University of Washington — Embedded Systems Design  
