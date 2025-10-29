/*
* Pranav Ananthram
* 2122059
* 5/3/2025
* This is the FSM module for Lab 2. This file is used to define the state transitions and uses 4 main states. Off, Stop, Warn, and Go. 
* Off: This represents the power off state and is the default state the code start in until the user powers it. A second press of the power button will cause the code to enter this state again and switch off all the LEDs
* Stop: Once the power button is pressed the code will enter this state and flash red, this code will transition between stop and go frequently until a button is pressed. In the event of person button being pressed it will go to warn, else it goes to go
* Warn: Once there is a person, the code will enter the warn state and shine yellow until the person button is pressed again to indicate the person has crossed. At which point it will go to go state.
* go: This state indicates that cars can go and will transition between stop until a button is pressed at which point it will enter warn or off when person or power is pressed respectively
*/
// This defines any libraries that we need and the LED and FSM header files to be able to do state transitions.
#include <stdint.h>
#include "led.h"
#include "fsm.h"
// This defines the 4 states and declares a variable state_t. I originally declared it as ps, but I encountered an error with identifiers thus I declared state and then ps(present state) to fix this error.
typedef enum {
    off,
    stop,
    warn,
    go
} state;
// Starts the code in state off until a button is pressed.
state ps = off;  

// This module contains the primary state transition logic with each state defining 
void trafficController(unsigned long power, unsigned long person) {
  switch(ps) {
    // When power is pressed the state will transition to stop or else it will remain in off state
      case off:
        if(power) {
          ps = stop;
        } else {
          ps = off;
        }
        break;
        // If no button is pressed it will transition to go state, when person is held it will go to warn state and when power is pressed it will enter off state
      case stop: 
        if(!power && !person) {
           ps = go;
        }
        else if (person) {
          ps = warn;
        } else if(power){
          ps = off;
        }
        break;
        // If person is pressed it will enter go state and when the power is pressed it will enter off state, else it remains in warn state.
      case warn:
        if(!power && !person) {
          ps = stop;
       } else if(power) {
          ps = off;
       } 
       break;
        // If no button is pressed it will transition to stop state, when person is held it will go to warn state and when power is pressed it will enter off state
       case go:
            if (!power && !person) {
                ps = stop;
         } else if (person) {
           ps = warn;
         }  else if (power) {
            ps = off;
         } 
            break;   
        }
  // This code is used to call the red_led, yellow_led and green_led modules which can activate the specific LEDs and as seen in this code, based on the state we are switching the LEDs on or off
        switch (ps) {
     // During off state all the LEDs are off
        case off:
            red_led(0);
            yellow_led(0);
            green_led(0);
            break;
      // During the stop state only the red LED is on
        case stop:
            red_led(1);
            yellow_led(0);
            green_led(0);
            break;
            // During the warn state only the yellow led is on
        case warn:
            red_led(0);
            yellow_led(1);
            green_led(0);
            break;
            // During the go state only the green led is on
        case go:
            red_led(0);
            yellow_led(0);
            green_led(1);
            break;
    }
}