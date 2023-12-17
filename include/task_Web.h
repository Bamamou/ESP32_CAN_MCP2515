/* 
| This is the website for updating the backend firmware and it is a JavaScript. 
| Here we onl;y have two sections, the loginIndex and the SeverIndex which are used in the main.cpp file.
|
*/
#ifndef __TASK_WEB_H__
#define __TASK_WEB_H__

//#include"Global_Const.h"
#include<Arduino.h>
#include "global_Variables.h"
#include<WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
//#include "Global_variable.h"
void onOTAStart();
void onOTAProgress(size_t current, size_t final);
void onOTAEnd(bool success);
// the task code that run the website
void taskCode_Web(void *pvParameters);

 #endif
 