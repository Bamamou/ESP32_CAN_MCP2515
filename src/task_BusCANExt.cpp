/******************************************************************************
 * task_BusCANExt.cpp
 * This file has the functions that take care of the external CAN Bus
 *****************************************************************************/

#include "task_BusCANExt.h"

// Code for the task CANBus
void taskCode_BusCANExt(void *pvParameters)
{
    // Init CAN connection
    ACAN2515Settings settings(8 * 1000UL * 1000UL, 500UL * 1000UL); // CAN bit rate 250 kb/s

    uint16_t errorCode = CANExt.begin(settings, NULL);
    if (0 == errorCode)
    {
        Serial.println("CAN OK");
    }
    else
    {
        Serial.print("CAN ERROR: 0x");
        Serial.println(errorCode, HEX);
    }

    // // Configure the CANRecv objects
    // MCUAPTRecv1.confToCanExt(addrMCUAPTRecv1, MCUPack1Analysis, 3000);
    // MCUAPTRecv2.confToCanExt(addrMCUAPTRecv2, MCUPack2Analysis, 3000);
    // chargerRecv.confToCanExt(addrChargerRecv, chargerPackAnalysis, 5000);
    // configure the DHT sensor 
      DHT_Send.confToCanExt(addrDHTSend, prepareCAN_WheatherData_Out, 50);
    // If the BMS data is coming via CAN
    if (p_ECUHardwareVersion == 1)
    {
        BMSRecv1.confToCanExt(addrSmartBMSRecv1, SmartBMSPack1Analysis, 3000);
        BMSRecv2.confToCanExt(addrSmartBMSRecv2, SmartBMSPack2Analysis, 3000);
        BMSRecv3.confToCanExt(addrSmartBMSRecv3, SmartBMSPack3Analysis, 3000);
        BMSRecv4.confToCanExt(addrSmartBMSRecv4, SmartBMSPack4Analysis, 3000);
        BMSRecv5.confToCanExt(addrSmartBMSRecv5, SmartBMSPack5Analysis, 3000);
        BMSRecv6.confToCanExt(addrSmartBMSRecv6, SmartBMSPack6Analysis, 3000);
        BMSRecv7.confToCanExt(addrSmartBMSRecv7, SmartBMSPack7Analysis, 3000);
        BMSRecv8.confToCanExt(addrSmartBMSRecv8, SmartBMSPack8Analysis, 3000);
        BMSRecv9.confToCanExt(addrSmartBMSRecv9, SmartBMSPack9Analysis, 3000);
        BMSRecv10.confToCanExt(addrSmartBMSRecv10, SmartBMSPack10Analysis, 3000);
        BMSRecv11.confToCanExt(addrSmartBMSRecv11, SmartBMSPack11Analysis, 3000);
        BMSRecv12.confToCanExt(addrSmartBMSRecv12, SmartBMSPack12Analysis, 3000);
        BMSRecv13.confToCanExt(addrSmartBMSRecv13, SmartBMSPack13Analysis, 3000);
        BMSRecv14.confToCanExt(addrSmartBMSRecv14, SmartBMSPack14Analysis, 3000);
        BMSRecv15.confToCanExt(addrSmartBMSRecv15, SmartBMSPack15Analysis, 3000);
        BMSRecv16.confToCanExt(addrSmartBMSRecv16, SmartBMSPack16Analysis, 3000);
        BMSRecv17.confToCanExt(addrSmartBMSRecv17, SmartBMSPack17Analysis, 3000);
    }

    // Configure the CANSend objects
    // MCUAPTSend.confToCanExt(addrMCUAPTSend, prepareCANMCUOut, 50);
    // chargerSend.confToCanExt(addrChargerSend, prepareCANChargerOut, 1000);

    // //  Adjust times interval for HMI packets
    // HMISend1.confToCanExt(addrHMISend1, prepareCANHMI1Out, 25);
    // HMISend2.confToCanExt(addrHMISend2, prepareCANHMI2Out, 25);
    // HMISend3.confToCanExt(addrHMISend3, prepareCANHMI3Out, 25);
    // HMISend4.confToCanExt(addrHMISend4, prepareCANHMI4Out, 25);

    while (true)
    {
        // Start execution debug
        task_BusCANExt.initDebugExec();

        // Checks incoming data from the CANBus
        // Use CAN
        CANExt.poll();

        // If some CAN data is available
      
        while (CANExt.available())
        {
            // Receive CAN Data
            CANExt.receive(CANExtReceiveFrame);

            // if(CANExtReceiveFrame.id == addrMCUAPTRecv1)
            //     Serial.printf("%l\n", millis());
            // wzh20230516

            // The function checkNAnalyze return true if the ID matches, so if the return is true the function continue jumps all other parts to get next packet
            if (BMSRecv1.checkNAnalyze())
                continue;
            if (BMSRecv2.checkNAnalyze())
                continue;
            if (BMSRecv3.checkNAnalyze())
                continue;
            if (BMSRecv4.checkNAnalyze())
                continue;
            if (BMSRecv5.checkNAnalyze())
                continue;
            if (BMSRecv6.checkNAnalyze())
                continue;
            if (BMSRecv7.checkNAnalyze())
                continue;
            if (BMSRecv8.checkNAnalyze())
                continue;
            if (BMSRecv9.checkNAnalyze())
                continue;
            if (BMSRecv10.checkNAnalyze())
                continue;
            if (BMSRecv11.checkNAnalyze())
                continue;
            if (BMSRecv12.checkNAnalyze())
                continue;
            if (BMSRecv13.checkNAnalyze())
                continue;
            if (BMSRecv14.checkNAnalyze())
                continue;
            if (BMSRecv15.checkNAnalyze())
                continue;
            if (BMSRecv16.checkNAnalyze())
                continue;
            if (BMSRecv17.checkNAnalyze())
                continue;
            // if (chargerRecv.checkNAnalyze())
            //     continue;
            // if (MCUAPTRecv1.checkNAnalyze())
            //     continue;
            // if (MCUAPTRecv2.checkNAnalyze())
            //     continue;
        }
          
       

        // Checks connection times
        CANExtWatchDog();

        // Send data to the charger if it is connected

        // if (vehicleInfo.isChargerConnected)
        // {
        //     chargerSend.prepareNSend();
        // }

        // // Send CAN data if the bike passed the initCheckup
        // if (vehicleInfo.passedInitCheckup)
        // {
        //     // Send the CAN packets out, respecting an interval

        //     // Send CAN packet to the MCU
        //     MCUAPTSend.prepareNSend();

        //     // Send CAN packets to the HMI

        //     HMISend1.prepareNSend();
        //     HMISend2.prepareNSend();
        //     HMISend3.prepareNSend();
        //     HMISend4.prepareNSend();
        // }

        // End execution debug
        task_BusCANExt.endDebugExec(uxTaskGetStackHighWaterMark(NULL));

        // Put the task to sleep
        vTaskDelay(task_BusCANExt.getInterval() / portTICK_PERIOD_MS);
    }
}

// Function that monitors CAN connection times
void CANExtWatchDog()
{

    // Analyzes the time when the charger packet was received, to detect if the vehicle is charging or not
    // if (chargerRecv.checkConn())
    // {
    //     // If the charger start to send packet, it means that it is connected
    //     vehicleInfo.isChargerConnected = true;

    //     // If the key is ON and the charger connected, the bike always get around 0.4A from it, even that is not charging
    //     // So the isCharging flag is true when the current is bigger that 0.5 AND the key is ON
    //     // Or when the current is bigger than 0 AND the key is off
    //     if (inputs.key)
    //         vehicleInfo.isCharging = (chargerData.current > 0.5);
    //     else
    //         vehicleInfo.isCharging = (chargerData.current > 0);
    // }
    // else
    // {
    //     // If the charger is disconnected, force everything related to 0 and false
    //     vehicleInfo.isChargerConnected = false;
    //     vehicleInfo.isCharging = false;
    //     chargerData.voltage = 0;
    //     chargerData.current = 0;
    //     chargerData.statusByte = 0;
    //     // Serial.printf("1234567890\n");
    // }

    // if (!MCUAPTRecv1.checkConn())
    // {
    //     MCUData.voltage = 0;
    //     MCUData.busCurrent = 0;
    //     MCUData.phaseCurrent = 0;
    //     MCUData.rpm = 0;
    //     // Serial.printf("asfhsdbdfbvefdgsbdxbwdsfbcvdsb dsfsdbbdssd\n");
    //     // sleep(100);
    // }

    // if (!MCUAPTRecv2.checkConn())
    // {
    //     MCUData.motorTemperature = 0;
    //     MCUData.controllerTemperature = 0;
    //     MCUData.throttle = 0;
    //     MCUData.lowByteStatus = 0;
    //     MCUData.highByteStatus = 0;
    //     MCUData.lowByteError = 0;
    //     MCUData.highByteError = 0;
    // }
}