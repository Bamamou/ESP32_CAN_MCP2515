/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * DHT.h
 * Header for DHT.cpp
 * DHT model DHT11
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef __DHT__
#define __DHT__

#include <Arduino.h>
#include "global_Constants.h"
#include "global_Variables.h"

// Analyzes the packet 4 received from the SmartBMS via CAN
void WheatherData(uint8_t *CANDataArray);

// Send the sensor data via CAN 
void prepareCAN_WheatherData_Out() ;

#endif