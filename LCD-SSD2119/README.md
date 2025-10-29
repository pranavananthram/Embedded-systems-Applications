## 🧩 Task 1

---

### Section 1.A — LCD Floating Point Display

#### **Procedure**
The objective of this procedure is to familiarize ourselves with the LCD display and use the provided driver functions to change the color of the screen and modify the `LCD_PrintFloat()` function to display floating-point numbers.

To achieve this, we used the `sprintf()` function to convert the float into a formatted string:
sprintf(buffer, "%.2f", number);
The %.2f format specifier ensures the number is rounded and displayed with exactly two digits after the decimal point.
The resulting string is stored in a character buffer and then passed to LCD_PrintString(), which handles displaying the value on the LCD.

### **Result 1.B**

We successfully printed floating-point numbers on the LCD and verified the implementation with various test values.
Additionally, we changed the LCD background color using the provided functions:
int main(void) {
  LCD_Init();    
  LCD_ColorFill(Color4[5]); // Changed the color to magenta
  LCD_PrintFloat(3.454655);
  while (1) {}
  return 0;
}
This functionality was later reused for displaying temperature values.

---

## Section 1.B — Temperature Display on LCD

### **Procedure**

The objective of this procedure is to display the on-board temperature of the TM4C microcontroller on the LCD screen, using the modified `PrintFloat()` function to show the temperature in both **Celsius** and **Fahrenheit**.

- The temperature was calculated from the ADC value using the provided conversion formula.  
- Two buttons (**PJ0** and **PJ1**) were configured to dynamically switch the system clock frequency between **12 MHz** and **120 MHz** via interrupts, with the current frequency displayed on-screen.  
- `ADC0SS3_Handler` captures new ADC readings (interrupt-based).  
- `port_J_handler` responds to button presses, reinitializes the PLL, and updates the display accordingly.

### **Result 1.B**

We successfully displayed:

- The current board temperature in both **Celsius** and **Fahrenheit**  
- The **PLL clock frequency** on the LCD  

The system dynamically switched between **12 MHz** and **120 MHz** frequencies while maintaining a stable **60 Hz update rate**, meeting all requirements from Lab 3.

---

## Section 1.C — Virtual Buttons on Touchscreen

### **Procedure**

The goal of this procedure is to use the resistive touchscreen to create two virtual buttons that control the PLL frequency instead of using the onboard buttons (**PJ0** and **PJ1**).

- We used the functions `Touch_ReadX()` and `Touch_ReadY()` to detect screen touches and defined coordinate ranges representing each virtual button.  
- If a touch is detected within a specific range, the PLL frequency is updated accordingly.  
- Visual indicators were drawn on the screen to highlight the two frequency buttons.

### **Result 1.C**

We successfully implemented virtual buttons and verified that touch inputs within defined coordinate ranges correctly updated the PLL frequency to **12 MHz** and **120 MHz**.
