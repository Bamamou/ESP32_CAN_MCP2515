/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * DHT.h
 * Header for DHT.cpp
 * DHT model DHT11
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef __DHT__
#define __DHT__

#include <Arduino.h>
#include "DHT.h"
#include "global_Constants.h"
#include "global_Variables.h"

// Send the sensor data via CAN 
void prepareCAN_WheatherData_Out(){
    DHT_Send.resetData();
    digitalRead(pinTXD1);
} ;

#endif