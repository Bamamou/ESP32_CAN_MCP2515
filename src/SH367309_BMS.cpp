/******************************************************************************
 * SH367309_BMS.cpp
 * This file has functions that are used in the SH367309_BMS task
 *****************************************************************************/

#include "SH367309_BMS.h"


void calcAvgBatteryTemperatureSmartBMS()
{
    // Calcute the average temperature
    uint8_t countAverage = 0;
    double auxAverage = 0;

    BMSData.temperatures[0] = BMSData.HighestTemperature;
    BMSData.temperatures[1] = BMSData.LowerTemperature;
    // Go through the array, checking the temperature of the temp probes in the battery (temperatures 2, 3, 4 and 5), summing and counting
    // The checking is done because sometimes the sensor might not be connected or passing wrong data, this was based on Gen1 code
    auxAverage = 0;
    for (uint8_t x = 2; x < 5; x++) // Adjusted to 5 because currently only 3 channels of temperature available by CAN in SmartBMS
    {
        if (BMSData.temperatures[x] > -70 && !(BMSData.temperatures[x] == 0xFFFF))
        {
            auxAverage += BMSData.temperatures[x];
            countAverage++;
        }
    }
    int16_t auxTemperature = (int16_t)(auxAverage / (double)countAverage);

    // Smooth the BMS temperature
    BMSData.avgBatteryTemperature = avgBMSTemp.addNCalcAvg(auxTemperature);
}

// Converts the cell voltages of BMS data from double to uint8_t
// Voltage of each cell. Value 0 = 2V. Incrementing of 0.01V each bit increment.
uint8_t cellVoltageToSaveInFlash(double cellVoltage)
{
    // If the cell voltage is less than 2V, returns 0
    if (cellVoltage < 2.0)
    {
        return 0;
    }
    // If the cell voltage is bigger than 4.55V, returns 255. It means the end of scale
    else if (cellVoltage > 4.55)
    {
        return 255;
    }
    // If it's between scale, converts
    else
    {
        return (uint8_t)((cellVoltage - 2.0) * 100.0);
    }
}

// Analyzes the packet 1 received from the SmartBMS via CAN
void SmartBMSPack1Analysis(uint8_t *CANDataArray)
{
    BMSData.cellsVoltage[0] = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    BMSData.cellsVoltage[1] = ((double)uint8To_Uint16(CANDataArray[4], CANDataArray[5])) / 1000.0;
    BMSData.cellsVoltage[2] = ((double)uint8To_Uint16(CANDataArray[6], CANDataArray[7])) / 1000.0;
 
  
}

// Analyzes the packet 2 received from the SmartBMS via CAN
void SmartBMSPack2Analysis(uint8_t *CANDataArray)

{
    BMSData.cellsVoltage[3] = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    BMSData.cellsVoltage[4] = ((double)uint8To_Uint16(CANDataArray[4], CANDataArray[5])) / 1000.0;
    BMSData.cellsVoltage[5] = ((double)uint8To_Uint16(CANDataArray[6], CANDataArray[7])) / 1000.0;

}

// Analyzes the packet 3 received from the SmartBMS via CAN
void SmartBMSPack3Analysis(uint8_t *CANDataArray)
{
    BMSData.cellsVoltage[6] = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    BMSData.cellsVoltage[7] = ((double)uint8To_Uint16(CANDataArray[4], CANDataArray[5])) / 1000.0;
    BMSData.cellsVoltage[8] = ((double)uint8To_Uint16(CANDataArray[6], CANDataArray[7])) / 1000.0;

}

// Analyzes the packet 4 received from the SmartBMS via CAN
void SmartBMSPack4Analysis(uint8_t *CANDataArray)
{
    BMSData.cellsVoltage[9] = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    BMSData.cellsVoltage[10] = ((double)uint8To_Uint16(CANDataArray[4], CANDataArray[5])) / 1000.0;
    BMSData.cellsVoltage[11] = ((double)uint8To_Uint16(CANDataArray[6], CANDataArray[7])) / 1000.0;
  
}

// Analyzes the packet 5 received from the SmartBMS via CAN
void SmartBMSPack5Analysis(uint8_t *CANDataArray)
{
    BMSData.cellsVoltage[12] = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    BMSData.cellsVoltage[13] = ((double)uint8To_Uint16(CANDataArray[4], CANDataArray[5])) / 1000.0;
    BMSData.cellsVoltage[14] = ((double)uint8To_Uint16(CANDataArray[6], CANDataArray[7])) / 1000.0;

}

// Analyzes the packet 6 received from the SmartBMS via CAN
void SmartBMSPack6Analysis(uint8_t *CANDataArray)
{
    BMSData.cellsVoltage[15] = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    BMSData.voltage = ((double)uint8To_Uint32(CANDataArray[4], CANDataArray[5], CANDataArray[6], CANDataArray[7])) / 1000.0;

}

// Analyzes the packet 7 received from the SmartBMS via CAN
void SmartBMSPack7Analysis(uint8_t *CANDataArray)
{
    BMSData.SOC =          (double)(CANDataArray[3]); 
    BMSData.Positive_Current  = (double)(CANDataArray[4]);
    BMSData.Negetive_current  = (double)(CANDataArray[5]);
    BMSData.current =      (double)uint8To_Uint16(CANDataArray[6], CANDataArray[7]);
}

// Analyzes the packet 8 received from the SmartBMS via CAN
void SmartBMSPack8Analysis(uint8_t *CANDataArray)
{
    BMSData.temperatures[1] = ((uint8To_Int16(CANDataArray[2], CANDataArray[3]))) / 10.0;
    BMSData.temperatures[2] = ((uint8To_Int16(CANDataArray[4], CANDataArray[5]))) / 10.0;
    BMSData.DischargingContactorStatus = CANDataArray[6]; // this represent the discharge MOS
    BMSData.ChargingContactorStatus = CANDataArray[7]; // this represent the charge MOS
    calcAvgBatteryTemperatureSmartBMS();

}

// Analyzes the packet 9 received from the SmartBMS via CAN
void SmartBMSPack9Analysis(uint8_t *CANDataArray)
{

    // BMSData.DischargingOverCurrentAlarm = CANDataArray[0];
    // BMSData.ChargingOverCurrentAlarm = CANDataArray[1];
    // BMSData.AbnormalDischargingAlarm = CANDataArray[2];
    // BMSData.AbnormalChargingAlarm = CANDataArray[3];
}

// Analyzes the packet 10 received from the SmartBMS via CAN
void SmartBMSPack10Analysis(uint8_t *CANDataArray)
{
    // BMSData.temperatures[2] = ((uint8To_Int16(CANDataArray[0], CANDataArray[1])) - 400) / 10.0;
    // BMSData.temperatures[3] = ((uint8To_Int16(CANDataArray[2], CANDataArray[3])) - 400) / 10.0;
    // BMSData.temperatures[4] = ((uint8To_Int16(CANDataArray[4], CANDataArray[5])) - 400) / 10.0;
    // BMSData.temperatures[5] = ((uint8To_Int16(CANDataArray[6], CANDataArray[7])) - 400) / 10.0;

    // Calculates the battery average temperature
 
}

// Analyzes the packet 11 received from the SmartBMS via CAN
void SmartBMSPack11Analysis(uint8_t *CANDataArray)
{

    // BMSData.PackStatusHighByte = CANDataArray[0];
    // BMSData.PackStatusLowByte = CANDataArray[1];
    // BMSData.ProtectionHighByte = CANDataArray[2];
    // BMSData.ProtectionLowByte = CANDataArray[3];
    // BMSData.AlarmHighestLevel = (double)uint8To_Uint16(CANDataArray[4], CANDataArray[5]);
    // BMSData.BatteryChargingConditionsMeet = CANDataArray[6];
    // BMSData.BatteryDischargingConditionsMeet = CANDataArray[7];
}

// Analyzes the packet 12 received from the SmartBMS via CAN
void SmartBMSPack12Analysis(uint8_t *CANDataArray)
{
    // BMSData.ChargingContactorStatus = CANDataArray[0];
    // // this is an  apprximated value of the set capacity and the remaining capacity is set based on the SOC for Evoke diagnostic app
    // BMSData.batteryPhysicalCapacity = 100;                           // Not sure
    // BMSData.batteryRemainingCapacity = (double)(BMSData.SOC) * 0.98; //
}

// Analyzes the packet 13 received from the SmartBMS via CAN
void SmartBMSPack13Analysis(uint8_t *CANDataArray)
{
    // BMSData.voltage = ((double)uint8To_Uint16(CANDataArray[0], CANDataArray[1])) / 100.0;
    // BMSData.current = (((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) - 10000) / 10.0;
    // BMSData.FullCapacity = ((double)uint8To_Uint16(CANDataArray[6], CANDataArray[7])) / 100.0;
    
}

// Analyzes the packet 14 received from the SmartBMS via CAN
void SmartBMSPack14Analysis(uint8_t *CANDataArray)
{
    // BMSData.cellHighestVoltageValue = ((double)uint8To_Uint16(CANDataArray[0], CANDataArray[1])) / 1000.0;
    // BMSData.cellLowestVoltageValue = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    // BMSData.cellHighestVoltageNumber = CANDataArray[4];
    // BMSData.cellLowestVoltageNumber = CANDataArray[5];
    // BMSData.HighestTemperature = ((uint8To_Int16(CANDataArray[0], CANDataArray[1])) - 400) / 10.0;
    // BMSData.LowerTemperature = ((uint8To_Int16(CANDataArray[2], CANDataArray[3])) - 400) / 10.0;
}

// Analyzes the packet 15 received from the SmartBMS via CAN
void SmartBMSPack15Analysis(uint8_t *CANDataArray)
{
    // BMSData.SOH = (double)uint8To_Uint16(CANDataArray[0], CANDataArray[1]);
    // BMSData.RunningTime = (double)uint8To_Uint16(CANDataArray[2], CANDataArray[3]);
    // BMSData.CycleTime = (double)uint8To_Uint16(CANDataArray[4], CANDataArray[5]);
    // BMSData.NumberofVoltage = CANDataArray[6];
    // BMSData.NumberofTemperature = CANDataArray[7];
    

}

// Analyzes the packet 16 received from the SmartBMS via CAN
void SmartBMSPack16Analysis(uint8_t *CANDataArray)
{
    // BMSData.TotalOvervoltageAlarm = CANDataArray[0];
    // BMSData.SimpleOvervoltageAlarm = CANDataArray[1];
    // BMSData.TotalUndervoltageAlarm = CANDataArray[2];
    // BMSData.SimpleUndervoltageAlarm = CANDataArray[3];
    // BMSData.DischargingHighTemperatureAlarm = CANDataArray[4];
    // BMSData.ChargingHighTemperatureAlarm = CANDataArray[5];
    // BMSData.DischargingLowTemperatureAlarm = CANDataArray[6];
    // BMSData.ChargingLowTemperatureAlarm = CANDataArray[7];
}

// Analyzes the packet 17 received from the SmartBMS via CAN
void SmartBMSPack17Analysis(uint8_t *CANDataArray)
{
    // BMSData.cellsVoltage[20] = ((double)uint8To_Uint16(CANDataArray[0], CANDataArray[1])) / 1000.0;
    // BMSData.cellsVoltage[21] = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    // BMSData.cellsVoltage[22] = ((double)uint8To_Uint16(CANDataArray[4], CANDataArray[5])) / 1000.0;
    // BMSData.cellsVoltage[23] = ((double)uint8To_Uint16(CANDataArray[6], CANDataArray[7])) / 1000.0;
}

// Analyzes the packet 18 received from the SmartBMS via CAN
void SmartBMSPack18Analysis(uint8_t *CANDataArray)
{
    // BMSData.cellsVoltage[24] = ((double)uint8To_Uint16(CANDataArray[0], CANDataArray[1])) / 1000.0;
    // BMSData.cellsVoltage[25] = ((double)uint8To_Uint16(CANDataArray[2], CANDataArray[3])) / 1000.0;
    // BMSData.cellsVoltage[26] = ((double)uint8To_Uint16(CANDataArray[4], CANDataArray[5])) / 1000.0;
    // BMSData.cellsVoltage[27] = ((double)uint8To_Uint16(CANDataArray[6], CANDataArray[7])) / 1000.0;
}


// void prepareCANSmartBMSOut () 

//  {

//     SmartBMSSend.resetData();

//      // The the main contactor can be closed if the below condition is met.
//     if ((vehicleInfo.isChargerConnected==false))    
//     {
//         SmartBMSSend.writeByte(SmartBMSSend_byteDischargingContactorControl, 1);   // both contactor are closed (current can pass)
//     }
//      // The main contactor will be closed during charging process but the Sevcon cannot have HV if this condition is met.
//     else if ((vehicleInfo.isChargerConnected==true)&&(BMSData.voltage>=117.7)&&(BMSData.cellHighestVoltageValue>=4201))  
//     {
//         SmartBMSSend.writeByte(SmartBMSSend_byteChargingContactorControl, 0); // we open the small contactor that gives HV to the Sevcon
//         SmartBMSSend.writeByte(SmartBMSSend_byteDischargingContactorControl, 0); // We keep the main contactor closed for charing purpose
//     }
    
    
//  }
