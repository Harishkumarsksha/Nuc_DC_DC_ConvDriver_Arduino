/**
 * @file BLE_Voltages.h
 * @author Harish
 * @brief 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BLE_VOLTAGES_H__
#define BLE_VOLTAGES_H__


#include <Arduino.h>
#include "stm32h743xx.h"
#include "main.h"

#include "algo.h"

typedef enum {
    BMS_VERSION_REQ=0x0A,
    BMS_DATA_SINGLE_REQ,
    BMS_DATA_AVERAGE_REQ,
    BMS_ENABLE_BYPASS_REQ,
    BMS_DISABLE_BYPASS_REQ,

}BLE_VOLTAGES_REQUESTS;

typedef struct 
{   
    uint16_t byteCount=1000;
    uint8_t BLE_buffer[];
    float VBAT[];
    float RES_TERM[];
    float TEMP[];
    BLE_VOLTAGES_REQUESTS BLE_REQUEST;
}BLE;

void getBLEdata(CBalgo *hCBalgo,BLE *hBLE);
void dataConvertBLE(CBalgo *hCBalgo,BLE *hBLE);

#endif 