/* 

 */
#ifndef __FUNC_74HC595_H__
#define __FUNC_74HC595_H__

#include <Arduino.h>

//Region of the 74HC595 register shifter or expander 
const uint8_t DATA_PIN = 15;   /* DS */ 
const uint8_t LATCH_PIN = 2;  /* SHCP */
const uint8_t CLOCK_PIN = 4;  /* STCP */

// How many of the shift registers
#define NUM_SHIFT_REGS 2

const uint8_t numOfRegisterPins = NUM_SHIFT_REGS * 8; // number of GPIOs
// This fuction toggle a specific GPIO
void Exp_Write(int desiredPin, boolean desiredState);

//A function to match each element of the array to a specific GPIO
void setRegisterPin(int index, int value);

//This function set all GPIO LOW
void clearRegisters();

//This function set all GPIO HIGH
void writeRegisters();

#endif