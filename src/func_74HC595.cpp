/* 
| This is the register shifter function called func_74HC595.cpp
| We can set the GPIOs , clear them, togle them with its function
|
*/
#include "func_74HC595.h"
bool toggle = false;
bool registers[numOfRegisterPins]; //An array to holdd the state of each GPIOs
//A function to match each element of the array to a specific GPIO
void setRegisterPin(int index, int value) {
  // Set an individual pin HIGH or LOW
  registers[index] = value;
}

//This function set all GPIO LOW
void clearRegisters() {
  // Reset all register pins
  for (int i = numOfRegisterPins - 1; i >= 0; i--) {
    registers[i] = LOW;
  }
}

// This function lets you make the shift register outputs
// HIGH or LOW in exactly the same way that you use digitalWrite().
void Exp_Write(uint8_t desiredPin, boolean desiredState){

  bitWrite(toggle,desiredPin,desiredState); //Change desired bit to 0 or 1 in "toggle"

   // turn off the output so the pins don't light up
   // while you're shifting bits:
  digitalWrite(LATCH_PIN, LOW); 
  // shift the bits out:
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, toggle); //Send "data" to the shift register

  //Toggle the latchPin to make "data" appear at the outputs
  digitalWrite(LATCH_PIN, HIGH); 
 
}

//This function set all GPIO HIGH
void writeRegisters() {
  // Set and display registers
  digitalWrite(LATCH_PIN, LOW);

  for (int i = numOfRegisterPins - 1; i >= 0; i--) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(DATA_PIN, registers[i]);
    digitalWrite(CLOCK_PIN, HIGH);
  }

  digitalWrite(LATCH_PIN, HIGH);
}






