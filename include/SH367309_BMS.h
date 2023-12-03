/******************************************************************************
 * SH367309_BMS.h
 * Header for SH367309_BMS.cpp
 * BMS Model SH367309
 *****************************************************************************/
#ifndef __SH367309_BMS__
#define __SH367309_BMS__

#include <Arduino.h>

#include "global_Constants.h"
#include "global_Variables.h"
#include "func_Misc.h"


// Calculates the average battery temperature and smooth it
void calcAvgBatteryTemperatureSmartBMS();

// Calculates the effiency
void calcEfficiency();

// Converts the cell voltages of BMS data from double to uint8_t
// Voltage of each cell. Value 0 = 3V. Incrementing of 0.01V each bit increment.
uint8_t cellVoltageToSaveInFlash(double cellVoltage);

// Analyzes the packet 1 received from the SmartBMS via CAN
void SmartBMSPack1Analysis(uint8_t *CANDataArray);

// Analyzes the packet 2 received from the SmartBMS via CAN
void SmartBMSPack2Analysis(uint8_t *CANDataArray);

// Analyzes the packet 3 received from the SmartBMS via CAN
void SmartBMSPack3Analysis(uint8_t *CANDataArray);

// Analyzes the packet 4 received from the SmartBMS via CAN
void SmartBMSPack4Analysis(uint8_t *CANDataArray);

// Analyzes the packet 5 received from the SmartBMS via CAN
void SmartBMSPack5Analysis(uint8_t *CANDataArray);

// Analyzes the packet 6 received from the SmartBMS via CAN
void SmartBMSPack6Analysis(uint8_t *CANDataArray);

// Analyzes the packet 7 received from the SmartBMS via CAN
void SmartBMSPack7Analysis(uint8_t *CANDataArray);

// Analyzes the packet 8 received from the SmartBMS via CAN
void SmartBMSPack8Analysis(uint8_t *CANDataArray);

// Analyzes the packet 9 received from the SmartBMS via CAN
void SmartBMSPack9Analysis(uint8_t *CANDataArray);

// Analyzes the packet 10 received from the SmartBMS via CAN
void SmartBMSPack10Analysis(uint8_t *CANDataArray);

// Analyzes the packet 11 received from the SmartBMS via CAN
void SmartBMSPack11Analysis(uint8_t *CANDataArray);

// Analyzes the packet 12 received from the SmartBMS via CAN
void SmartBMSPack12Analysis(uint8_t *CANDataArray);

// Analyzes the packet 13 received from the SmartBMS via CAN
void SmartBMSPack13Analysis(uint8_t *CANDataArray);

// Analyzes the packet 14 received from the SmartBMS via CAN
void SmartBMSPack14Analysis(uint8_t *CANDataArray);

// Analyzes the packet 15 received from the SmartBMS via CAN
void SmartBMSPack15Analysis(uint8_t *CANDataArray);

// Analyzes the packet 16 received from the SmartBMS via CAN
void SmartBMSPack16Analysis(uint8_t *CANDataArray);

// Analyzes the packet 17 received from the SmartBMS via CAN
void SmartBMSPack17Analysis(uint8_t *CANDataArray);

// Analyzes the packet 18 received from the SmartBMS via CAN
void SmartBMSPack18Analysis(uint8_t *CANDataArray);

// Prepares the CAN packet to send via can to the SmartBMS
void prepareCANSmartBMSOut();





#endif